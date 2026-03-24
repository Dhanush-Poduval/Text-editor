#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "memory.h"
#include <ctype.h>
int main(){
  struct termios curr_state;
  //activate raw_mode
  activate_rawmode(&curr_state);
  char c;
  //will read the byte of the char and the loop will run as long as its 1 
  while(read(STDIN_FILENO,&c,1)==1){
    if(c=='q'){
      break;
    }
    if(iscntrl(c)){
      printf("%d\n",c);
    }else{
      printf("%c\n",c);
    }
     };
  return 0;
};
