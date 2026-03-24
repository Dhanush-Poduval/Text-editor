#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
/*
 * function to activate raw mode (no need to press enter anymore for the terminal to read characters)
 * arguments - pointer to the terminal settings pointer so that values are changed to the original
 * get the current settings changes them using the c_lflag(local flag) item inside and setting it to the opposite of the current bits for echo and ICANON
 * echo - causes each key i type to be printed in the terminal && icanon - is to enable disable canonical mode
*/
struct termios org; //to store the old settings / configuration of the terminal
void activate_rawmode(struct termios *raw){
  tcgetattr(STDIN_FILENO,raw);
  atexit(deactivate_rawmode);
  org=*raw;
  raw->c_oflag &= ~(OPOST);
  raw->c_iflag &= ~(IXON | ICRNL); //disable ctrl + s ctrl+q
  raw->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // disable echo canonical mode ctrl+c ctrl+z ctrl+v 
  tcsetattr(STDIN_FILENO,TCSAFLUSH,raw);
};
//to deactivate the raw mode
void deactivate_rawmode(){
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&org);
};

