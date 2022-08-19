/* socket_client.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKETNAME "mynewsocket"

int main(int argc, char *argv[])
{
  char buffer[1024];
  int n, sock, len;
  struct sockaddr_un name;

  /******************************************************************************
  * YOUR TASK:                                                                  *
  * Create a new socket.                                                        *
  ******************************************************************************/
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
  	perror("client: socket");
  	exit(1);
  }
  
  // Create the address of the server.
  memset(&name, 0, sizeof(struct sockaddr_un));
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path, SOCKETNAME);
  len = sizeof(name.sun_family) + strlen(name.sun_path);

  // Connect to the server.
  if (connect(sock, (struct sockaddr *)&name, SUN_LEN(&name)) < 0)
  {
    perror("client: connect");
    exit(1);
  }

  /******************************************************************************
  * YOUR TASK:                                                                  *
  * Continuously read data from standard input and send the data to the socket. *
  ******************************************************************************/
  while((n = read(0, buffer, 1024)) > 0){
  	buffer[n] = '\0';
  	send(sock, buffer, n, 0);
  }
  
  close(sock);
  exit(0);
}
