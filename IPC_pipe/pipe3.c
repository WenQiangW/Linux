/*******************************************************************
	> File Name: pipe3.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Wed 01 Mar 2017 02:06:55 PM PST
 *******************************************************************/

// read close ,
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
		while(1)// write no close,but no write
		{
			write(pipefd[1],msg,strlen(msg));	
		}
		close(pipefd[1]);
	}
	else//father read
	{
		
		close(pipefd[1]);//close write
		int count = 5;
		char buf[128];
		while(1)
		{
			ssize_t _s = read(pipefd[0],buf,sizeof(buf)-1);
			if(_s>0)
			{
				buf[_s] ='\0';
				printf("child -<father:%s,_s: %d\n",buf,_s);
			}
			else if(_s ==0)
			{
				printf("write close\n");
				break;
			}
			count--;
			if(count == 0)
			{
				close(pipefd[0]);
				break;
			}
		}
		int status = 0;
		pid_t ret = waitpid(id,&status,0);
		if(ret > 0)
		{
			printf("exit code :%d ,signal :%d\n",\
					(status>>8)&0xff,status&0xff);
		}
	}

	return 0;
}
