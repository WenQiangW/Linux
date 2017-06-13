/*************************************************************************
	> File Name: server.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Fri 24 Feb 2017 11:29:46 AM PST
 ************************************************************************/

#include"comm.h"

int main()
{
	int msgid = CreateMsgQueue();
	printf("msgid:%d\n",msgid);
	sleep(5);

	
	char buf[SIZE];
	while(1){ //receive -> send
		ReceiveMsg(msgid,CLIENT_TYPE,buf);
		printf("client#:%s\n",buf);

		printf("Please Enter:");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = '\0';
		SendMsg(msgid,SERVER_TYPE,buf);
		}
		sleep(1);
	}
	sleep(5);
	DestoryMsgQueue(msgid);
	return 0;
}
