/*************************************************************************
	> File Name: server.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Thu 23 Feb 2017 10:17:45 AM PST
 ************************************************************************/


#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
int main()
{
	umask(0);
	if(mkfifo("./fifo",0666|S_IFIFO)<0)
	{
		perror("mkfifo");
		return 1;
	}
	
	int fd = open("./fifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}
	
	char buf[128];
	while(1)
	{
		ssize_t s = read(fd,buf,sizeof(buf));
		if(s>0)
		{
			buf[s] ='\0';
			printf("client:%s\n",buf);
		}
		else if(s ==0)
		{
			printf("client quit! server should quit\n");
			break;
		}
		else
		{
			perror("read");
			return 4;
		}
	}

	close(fd);
	return 0;
}
