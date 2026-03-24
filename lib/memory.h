#ifndef MEMORY_H
#define MEMORY_H
#include <termios.h>
void activate_rawmode(struct termios *raw);
void deactivate_rawmode(struct termios *raw);
#endif
