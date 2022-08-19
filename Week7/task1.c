#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int result;
	
   if(pid = fork()) 
   {
       printf("Usage: ./a.out string filename\n");
       return 0;
   }
   else if(pid > 0) // create child process
   {
       // child
       char str[64] = {0};
       sprintf(str, "echo %s", argv[1]); // copy command in str
       system(str); // exicute command
   }
   else if(pid == 0)
   {
       // parent
       char str[64] = {0};
       sprintf(str,"less %s",argv[2]); // copy command in str
       system(str); // exicute command
   }
   exit(0);
}
