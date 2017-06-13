#include"comm.h"


int commMsgQueue(int flags)
{
	//get key
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key <0)
	{
		perror("ftok");
		return -1;
	}
	int msg_id = msgget(key,flags);	
	if(msg_id <0)
	{
		perror("msgget");
		return -2;
	}
	return msg_id;
}
int CreateMsgQueue()//
{
	return commMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}
int GetMsgQueue()
{
	return commMsgQueue(IPC_CREAT);
}
int DestoryMsgQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;

}
int SendMsg(int msgid,long type,const char* info)
{
	struct msgbuf msg;
	msg.mtype = type;
	strcpy(msg.mtext,info);
	if(msgsnd(msgid,&msg,sizeof(msg.mtext),0)<0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}
int ReceiveMsg(int msgid,long type,char out[])
{
	struct msgbuf msg;
	if(msgrcv(msgid,&msg,sizeof(msg.mtext),type,0)<0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,msg.mtext);
	return 0;
}
