#ifndef _COMM_H
#define _COMM_H


#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define PATHNAME "./"
#define PROJ_ID 0x666
#define SIZE 128
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
struct msgbuf
{
	long mtype;
	char mtext[SIZE];
};

int commMsgQueue(int flags);
int CreateMsgQueue();
int GetMsgQueue();
int DestoryMsgQueue(int msgid);
int SendMsg(int msgid,long type,const char* info);
int ReceiveMsg(int msgid,long type,char out[]);
#endif
