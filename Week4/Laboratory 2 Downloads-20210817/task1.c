/* task1.c */
/*
This program defines a new unitid struct with some attributes. Then it either
open for writing, create if not exist or truncate the file named as "recordfile"
based on existing file. If the opened file is executable referring to the listing
operations, the unitcodes will be writen in a sequence of 3,1,2,0 (for loop) on
the corresponding offset of the "recordfile" file. If none of the operations 
execute, the program will exit.

*/
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
  int i, outfile;
  struct Record eachrec;

  if ((outfile = open("recordfile", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) {
    exit(1); 
    /*open(): O_WRONLY or O_CREAT or O_TRUNC 
    O_WRONLY: the file is opened for write only
    O_CREAT: create the file if it does not exist
    O_TRUNC: If the file is opened for writing, truncate the length of the file 
    		 to zero
    */
  }

  for (i = 3; i >= 0; i -=2) {
    eachrec.unitid = i;
    strcpy(eachrec.unitcode, unitcodes[i]);

    lseek(outfile, (long) i * sizeof(struct Record), SEEK_SET);
    /*
    lseek() function re-positions the file offset(offset) of a file referred to
    by the file descriptor fd, based on the position in th file specified by the
    last argument in the function whence.
    */
    
    /*
    SEEK_SET: The file offset is set to offset bytes from the beginning of the
    		  file
    */
    write(outfile, &eachrec, sizeof(struct Record));
    
   /*
   sizeof(): byte size of the message (not values)
   */

    if (i == 1) {
      i = 4;
    }
  }

  close(outfile);
  exit(0);
}
