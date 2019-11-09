#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<errno.h>

#include<string.h>

int main() {
  int fd;
  fd = open("/dev/random",O_RDONLY);
  if(fd == -1) {
    printf("error number %d: %s\n",errno,strerror(errno));
  }else {
    printf("successful file access!\n");
  }
  return 0;
}
