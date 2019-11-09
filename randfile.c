#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

#include<string.h>

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
    } else {
      if(status >= 0) printf("Reached end of file, only read %d bytes\n",status);
      else            printf("error number %d: %s\n",errno,strerror(errno));
    }
  }
  return 0;
}
