/************************************************************************
	> File Name: pipe1.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Wed 01 Mar 2017 01:47:16 PM PST
 ***********************************************************************/
// all write close  
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
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
	}
	else//father read
	{
		
		close(pipefd[1]);//close write
		int count =5;
		char buf[128];
		while(1)
		{
			ssize_t _s = read(pipefd[0],buf,sizeof(buf)-1);
			if(_s>0)
			{
				buf[_s] ='\0';
				printf("child -<father:%s,_s :%d\n",buf,_s);
			}
			else if(_s ==0)//write close,read over
			{
				printf("write close\n");
				break;
			}
		}
		if(waitpid(id,NULL,0)<0)
			return 3;
		close(pipefd[0]);
	}

	return 0;
}
