#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
//#include <stropts.h>

int _kbhit(void);
void clearScreen(int x);
//int settings;

#endif
