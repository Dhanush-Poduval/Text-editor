#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "memory.h"
#define CTRL_KEY(k) ((k)&0x1f)
/*
 * function to activate raw mode (no need to press enter anymore for the terminal to read characters)
 * arguments - pointer to the terminal settings pointer so that values are changed to the original
 * get the current settings changes them using the c_lflag(local flag) item inside and setting it to the opposite of the current bits for echo and ICANON
 * echo - causes each key i type to be printed in the terminal && icanon - is to enable disable canonical mode
*/ 

struct editor_config {
  int screen_rows;
  int screen_cols;
  struct termios org;
}E;
void initEditor() {
  if (get_window_size(&E.screen_rows, &E.screen_cols) == -1) error_handle("getWindowSize");
}
void activate_rawmode(struct termios *raw){
  tcgetattr(STDIN_FILENO,raw);
  if(tcgetattr(STDIN_FILENO,raw)==-1){
    error_handle("error in tcgetattr");
  }
  atexit(deactivate_rawmode);
  E.org=*raw;
  raw->c_oflag &= ~(OPOST);
  raw->c_iflag &= ~(IXON | ICRNL | INPCK | ISTRIP | IXON); //disable ctrl + s ctrl+q
  raw->c_cflag |= (CS8);
  raw->c_cc[VMIN]=0;
  raw->c_cc[VTIME]=1;
  raw->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // disable echo canonical mode ctrl+c ctrl+z ctrl+v 
  tcsetattr(STDIN_FILENO,TCSAFLUSH,raw);
  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,raw)==-1){
    error_handle("error in tcsetattr");
  }


};
int get_window_size(int *rows , int *cols){
  struct winsize ws;
  if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)==-1 || ws.ws_col==0){
    return -1;
  }else {
    *cols=ws.ws_col;
    *rows=ws.ws_row;
    return 0;
  }
};
void editor_draw_rows(){
  int n=24;
  for(int i=0;i<E.screen_rows;i++){
    write(STDOUT_FILENO,"~\r\n",3);
  }
}
char editor_read_key(){
  int n_read;
  char c;
  while(n_read=read(STDIN_FILENO,&c,1)!=1){
    if(n_read==-1 && errno!=EAGAIN) error_handle("read");
  }
  return c;
}
void editor_refresh_screen(){
  write(STDOUT_FILENO,"\x1b[2J",4);
  write(STDOUT_FILENO,"\x1b[H",3);
  editor_draw_rows();
  write(STDOUT_FILENO, "\x1b[H", 3);
}
void editor_process_key(){
  char c=editor_read_key();
  switch(c){
    case CTRL_KEY('q'):
      write(STDOUT_FILENO,"\x1b[2J",4);
      write(STDOUT_FILENO,"\x1b[H",3);
      exit(0);
      break;
  }
}

//to deactivate the raw mode
void deactivate_rawmode(){
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&E.org);
  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&E.org)==-1){
    error_handle("error in tcsetattr");
  }
};
void error_handle(char *s){
  write(STDOUT_FILENO,"\x1b[2J",4);
  write(STDOUT_FILENO,"\x1b[H",3);
  perror(s);
  exit(1);
}; 

