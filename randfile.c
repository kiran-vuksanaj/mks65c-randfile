#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

#include<string.h>

void print_ary(int *ary,size_t n);
int printerr(char *while_msg);

int main() {
  int fd;
  fd = open("/dev/urandom",O_RDONLY);
  if(fd == -1) {
    printf("error number %d: %s\n",errno,strerror(errno));
  }else {
    printf("successful file access!\n");
    int ary[10];
    int status;
    status = read(fd,ary, 10 * sizeof(int) );
    close(fd);
    if(status == 10 * sizeof(int) ) {
      printf("successful read from rand!\n");
      print_ary(ary,10);
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

      close(randfile);
      
      int arycopy[10];
      randfile = open("randary",O_RDONLY);
      status = read(randfile,arycopy, 10 * sizeof(int));
      if(status != 10 * sizeof(int)) {
	if(status == 01) return printerr("reading from randary");
	else {
	  printf("Reached end of file: only %d bytes read\n",status);
	  return 1;
	}
      }
      printf("Successfully read from file\n");

      print_ary(arycopy,10);

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
void print_ary(int *ary,size_t n) {
  short i;
  printf("[ ");
  for(i = 0; i < n; i++) {
    printf("%d ",ary[i]);
  }
  printf("]\n");
}
