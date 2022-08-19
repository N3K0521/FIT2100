/* exec-ls-alr.c */

#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid;
  char *params[] = {"/bin/ls", "-alR", 0};

  if ((pid = fork()) < 0) {     /* create a new process */
    perror("fork error");
    exit(1);
  } else if (pid == 0) {        /*  in the child process */
    execv("/bin/ls", params);
  } else {                      /* in the parent process */
    sleep(10);			
  }
  exit(0);
}
