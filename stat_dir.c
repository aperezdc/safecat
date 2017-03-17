/* Copyright (c) 2000, Len Budney. See COPYING for details. */

#include "stat_dir.h"
#include "strerr.h"
#include <sys/stat.h>
#include <unistd.h>

/* ****************************************************************** */
void stat_dir(char *dirname) {
  struct stat filestat;

  if(stat(dirname,&filestat) != 0) {
    strerr_die2sys(111,"safecat: fatal: ","could not stat directory ");
  }
  if( !S_ISDIR(filestat.st_mode) ) {
    strerr_die2x(111, "safecat: fatal: ","not a directory");
  }
  if((filestat.st_mode & S_IWUSR) != S_IWUSR) {
    strerr_die2x(111, "safecat: fatal: ","directory not writable");
  }
  filestat.st_mode = 0;
}
/* ****************************************************************** */
