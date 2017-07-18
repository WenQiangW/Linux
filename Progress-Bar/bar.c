/*******************************************************************
	> File Name: jindutiao.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Thu 16 Feb 2017 02:50:05 AM PST
 *******************************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
	int i=0;
	char bar[102];
	const char *label ="-\\|/";
	bar[0] = '\0';
	
	while(i<=100)
	{
		printf("[%-101s][%d%%][%c]\r",bar,i,label[i%4]);
		fflush(stdout);
		bar[i++] = '#';
		bar[i] = '\0';
		sleep(1);
	}
	printf("\n");
	
	return 0;
}
