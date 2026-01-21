#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  struct winsize w;

  if (ioctl(STDOUT_FILENO , TIOCGWINSZ, &w) >= 0){
    printf("Terminal height: %d lines \n", w.ws_row);
    printf("Terminal width: %d lines \n", w.ws_col);

  }else{
    perror("ioctl error!");
    return -1;
  }
  
  return 0;
}
