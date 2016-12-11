#ifndef __COLORS_H
#define __COLORS_H
#include <stdio.h>

// Foreground colors
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Background colors
#define ANSI_BGC_BLACK  "\x1b[40m"
#define ANSI_BGC_RED    "\x1b[41m"
#define ANSI_BGC_GREEN  "\x1b[42m"
#define ANSI_BGC_YELLOW "\x1b[43m"
#define ANSI_BGC_BLUE   "\x1b[44m" 
#define ANSI_BGC_MAGENTA "\x1b[45m"
#define ANSI_BGC_CYAN   "\x1b[46m"
#define ANSI_BGC_WHITE  "\x1b[47m"

#endif
