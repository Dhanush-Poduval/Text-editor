#ifndef MEMORY_H
#define MEMORY_H
#include <termios.h>
void initEditor(void);
void activate_rawmode(struct termios *raw);
void deactivate_rawmode(void);
char editor_read_key(void);
void editor_process_key(void);
void error_handle(char *s);
int get_window_size(int *a , int *b);
void editor_refresh_screen(void);
#endif
