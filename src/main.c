#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios raw;
int main(){
  //activate raw_mode
  activate_rawmode(*raw);
  char c;
  //will read the byte of the char and store it in memory until it reaches the 0 byte which is the end of the string 
  while(read(STDIN_FILENO,&c,1)==1);
  return 0;
};
