#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

#include<string.h>

int printerr(char *while_msg);

int main() {
  int fd;
  fd = open("/dev/random",O_RDONLY);
  if(fd == -1) {
    printf("error number %d: %s\n",errno,strerror(errno));
  }else {
    printf("successful file access!\n");
    int ary[10];
    int status;
    status = read(fd,ary, 10 * sizeof(int) );
    if(status == 10 * sizeof(int) ) {
      printf("successful read from rand!\n");

      short i;
      printf("[ ");
      for(i = 0; i < 10; i++) {
	printf("%d ",ary[i]);
      }
      printf("]\n");

      printf("open \"randary\"\n");

      int randfile = open("randary",O_CREAT | O_TRUNC | O_WRONLY,0644);
      if(randfile == -1) return printerr("opening randary");
      printf("successfully opened randary @fd = %d\n",randfile);
      status = write(randfile,ary, 10 * sizeof(int) );

      if(status != 10 * sizeof(int) ) {
	if(status == -1) return printerr("writing to randary");
	else {
	  printf("something weird happened: only %d characters written\n",status);
	  return 1;
	}
      }
      printf("wrote array to randfile\n");

    } else {
      if(status >= 0) printf("Reached end of file, only read %d bytes\n",status);
      else            printf("error number %d: %s\n",errno,strerror(errno));
    }
  }
  return 0;
}

int printerr(char *while_msg) {
  printf("error occured while [%s]: error %d: %s\n",while_msg,errno,strerror(errno));
  return 1;
}
