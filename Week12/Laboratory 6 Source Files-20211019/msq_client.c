/* msq_client.c */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSQKEY 34858
#define MSQSIZE 32

struct msgbuf
{
  long mtype;
  char mtext[MSQSIZE];
};

int main(int argc, char *argv[])
{
  key_t key;
  int n, msqid;
  struct msgbuf mbuf;

  // Get a message queue. The server must have created it.
  key = MSQKEY;
  if ((msqid = msgget(key, 0666)) < 0)
  {
    perror("client: msgget");
    exit(1);
  }

  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * Continuously read data from standard input and send the data as messages of type 1. *
  ***************************************************************************************/
  while((n=read(0, mbuf.mtext, sizeof(mbuf)))>0)
  {
  	mbuf.mtype = 1;
  	msgsnd(msqid, &mbuf, n, 0);
  }
  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * When an empty message is read, send a message of type 2 to indicate no more data.   *
  ***************************************************************************************/
  mbuf.mtype = 2;
  memset(mbuf.mtext, 0, MSQSIZE);
  //msgsnd(msqid, &mbuf, MSQSIZE, 0);
  exit(0);
}
