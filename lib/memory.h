#ifndef MEMORY_H
#define MEMORY_H
#include <termios.h>
void activate_rawmode(struct termios *raw);
void deactivate_rawmode(void);
void error_handle(char *s);
#endif
