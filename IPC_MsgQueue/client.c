/*************************************************************************
	> File Name: client.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Mon 27 Feb 2017 03:22:58 PM PST
 ************************************************************************/

#include"comm.h"
int main()
{
	int msgid = GetMsgQueue();
	printf("msgid:%d\n",msgid);
	char buf[SIZE];
	while(1){ //send -> receive
		printf("Please Enter: ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = '\0';
		SendMsg(msgid,CLIENT_TYPE,buf);
		}
	ReceiveMsg(msgid,SERVER_TYPE,buf);
	printf("server#:%s\n",buf);
	}
	return 0;
}
