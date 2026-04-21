#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "memory.h"
#include <ctype.h>

/*
 * Activate raw mode with all the flags added 
 * makes the read fucntion return when inactive for 1000 ms , return 0 as default 
 * prints characters ,and ascii values of special characters
 * breaks and deactivates mode when q is pressed
*/
int main(){
  struct termios curr_state;
  initEditor();
  //activate raw_mode
  activate_rawmode(&curr_state);
  char c;
  //will read the byte of the char and the loop will run as long as its 1 
  while(1){
    /*
    char c='\0';
    read(STDIN_FILENO,&c,1);
    if(c=='q'){
      break;
    }
    if(iscntrl(c)){
      printf("%d\r\n",c);
    }else{
      printf("%c\r\n",c);
    }
    if(c==CTRL_KEY('q')) break;
    */ 
    editor_refresh_screen();
    editor_process_key();
  };
  return 0;
};
