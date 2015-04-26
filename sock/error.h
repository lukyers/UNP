#ifndef __MYERROR_H
#define __MYERROR_H

#include <stdio.h>
#include <stdlib.h>

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);


#endif

