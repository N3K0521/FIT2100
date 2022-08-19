#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct Record {
  int unitid;
  char unitcode[8];
};

char *unitcodes[] = {"FIT2100", "FIT1047", "FIT3159", "FIT3142"};

int main(int argc, char *argv[])
{
  int i, odd, even;
  struct Record eachrec;
  char* warning = "Fail to open the file\n";
  
  int fd = open("recordfile", O_RDONLY);
  if (fd == -1){
  	write(1, warning, strlen(warning));
  }
  if ((odd = open("odd", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) {
    exit(1); 
  }
  if ((even = open("even", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) {
    exit(1); 
  }
  
  struct Record buf[4];
  warning = "Fail to read the file\n";
  int j;
  
  for (i = 1; i >= 0; i -= 1){
  	lseek(fd, (long)i * sizeof(struct Record), SEEK_SET);
  	j = read(fd, buf[i].unitcode, 16);//16
  	if (j < 0){
  		write(1, warning, strlen(warning));
  	}
  	write(1, buf[i].unitcode, j);
  
  if(i % 2 != 0){
  	lseek(odd, (long)i * sizeof(struct Record), SEEK_SET);
  	write(odd, buf[i].unitcode, j);
  	}
  	else{
  		lseek(even, (long)i * sizeof(struct Record), SEEK_SET);
  		write(even, buf[i].unitcode, j);
  	}
  	if (i == 0){
  		i = 4;
  	}
  	if (i == 2){
  		char newLine[] = "\n";
  		write(1, newLine, sizeof(newLine));
  		break;
  		}
  	}
  	
  	close(odd);
  	close(even);
  	exit(0);
  }
