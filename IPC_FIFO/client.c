/*************************************************************************
	> File Name: server.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Thu 23 Feb 2017 10:17:45 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
int main()
{
	
	int fd = open("./fifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}
	
	char buf[128];
	while(1)
	{
		printf("Please Enter: ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf));
		if(s>0)
		{
			buf[s-1] ='\0'; // huiche duojia yige huanhang
			
			write(fd,buf,strlen(buf));//wirte to pipe
		}
	}
	close(fd);
	return 0;
}
