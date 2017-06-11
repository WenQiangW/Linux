/*********************************************************************
	> File Name: mypipe.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Thu 23 Feb 2017 08:47:27 AM PST
 *********************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int pipefd[2] ={0,0};
	if(pipe(pipefd)<0)
	{
		perror("pipe");
		return 1;
	}
	
	pid_t id =fork();
	
	if(id <0)
	{
		perror("fork");
		return 2;
	}
	else if(id == 0)//child write
	{
		
		close(pipefd[0]);//close read
		const char *msg ="hello world";
		int count =5;
		while(count--)
		{
			write(pipefd[1],msg,strlen(msg));
			sleep(1);
		}
		close(pipefd[1]);
		exit(0);
	}
	else//father read
	{
		
		close(pipefd[1]);//close write
		int count =5;
		char buf[128];
		while(count--)
		{
			ssize_t _s = read(pipefd[0],buf,sizeof(buf)-1);
			if(_s>0)
			{
				buf[_s] ='\0';
				printf("child -<father:%s\n",buf);
			}
			else if(_s ==0)
			{
				printf("write close\n");
				break;
			}
		}
		
		close(pipefd[0]);
	}
	
	return 0;
}

