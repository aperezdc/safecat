/* Copyright (c) 2000, Len Budney. See COPYING for details. */

#include "hassgact.h"
#include "stralloc.h"
#include "strerr.h"
#include <signal.h>
#include <unistd.h>

/* ****************************************************************** */
extern stralloc tmppath;
void alarm_handler(int sig) {
  unlink(tmppath.s);
  strerr_die2x(111,"safecat: fatal: ","Timer has expired; giving up");
}
/* ****************************************************************** */


/* ****************************************************************** 
   This function was pretty much lifted from Qmail code.  Thanks to
   Professor Bernstein. 
   ****************************************************************** */
void set_handler(int sig, void (*h)()) {
#ifdef HASSIGACTION
  struct sigaction sa;
  sa.sa_handler = h;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(sig,&sa,(struct sigaction *) 0);
#else
  signal(sig,h);
#endif
}
/* ****************************************************************** */
