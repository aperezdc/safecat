/* Copyright (c) 2000, Len Budney. See COPYING for details. */

/* Signal handler for SIGALRM and signal handler setter. */
void set_handler(int sig, void (*f)());
void alarm_handler(int sig);
