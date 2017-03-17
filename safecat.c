/* Copyright (c) 2000, Len Budney. See COPYING for details. */

/* safecat.c -- write stdin to a directory using the maildir algorithm.
 * 
 * Safecat implements the maildir algorithm of Professor DJ Bernstein,
 * which is also used by his mail agent Qmail.  This program can be
 * used to deliver data to a qmail maildir from a shell script,
 * safely, or for other related purposes (such as spooling data to a
 * directory).
 */

#include "alloc.h"
#include "sig.h"
#include "stat_dir.h"
#include "stralloc.h"
#include "strerr.h"
#include "subfd.h"
#include "tempfile.h"
#include "version.h"
#include "writefile.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

/* Function prototypes. */
static
void die_nomem() { strerr_die2x(111,"safecat: fatal: ","out of memory"); }
stralloc tmppath = {0};

/* ****************************************************************** */
int main(int argc, char *argv[]) {
  char *tempdir  = NULL;
  char *destdir  = NULL;
  int   outfd    = 0;
  stralloc dstpath = {0};
  stralloc outfile = {0};
  stralloc outpath = {0};
  struct stat filestat;
  unsigned int count = 0;

  /* Check that we were called with the correct number of arguments. */
  if(argc != 3) {
    strerr_die2x(100, "safecat: usage: ","safecat <tempdir> <destdir>");
  }

  /* Scan the command line arguments, to get the temp directory
     and destination directory names. */
  tempdir = argv[1];
  destdir = argv[2];

  /* Declare a handler for SIGALRM so we can time out. */
  set_handler(SIGALRM, alarm_handler);

  /* Step 1:  Check that the supplied directories are OK. */
  stat_dir(tempdir);
  stat_dir(destdir);

  /* Step 2:  Stat the temporary file.  Wait for ENOENT as a response. */
  for(count=1;;count++) {
    /* Get the temporary filename to use now for dumping data. */
    mk_tempfile(&outfile);
    if (!stralloc_cats(&outpath,tempdir)) die_nomem();
    if (!stralloc_append(&outpath, "/")) die_nomem();
    if (!stralloc_cat(&outpath,&outfile)) die_nomem();
    if(stat(outpath.s,&filestat) == -1 && errno == ENOENT) {
      if (!stralloc_cats(&dstpath, destdir)) die_nomem();
      if (!stralloc_append(&dstpath, "/")) die_nomem();
      if (!stralloc_cat(&dstpath,&outfile)) die_nomem();

      if (!stralloc_cats(&tmppath, tempdir)) die_nomem();
      if (!stralloc_append(&tmppath, "/")) die_nomem();
      if (!stralloc_cat(&tmppath,&outfile)) die_nomem();
      break;
    }

    /* Try up to 5 times, every 2 seconds. */
    if(count == 5) {
      strerr_die2x(111, "safecat: fatal: ","could not stat temporary file");
    }

    /* Wait 2 seconds, and try again. */
    stralloc_copys(&outfile,"");
    stralloc_copys(&outpath,"");
    sleep(2);
  }

  /* Step 4:  Create the file tempdir/time.MusecPpid.host */
  alarm(86400);
  outfd = open(tmppath.s,O_WRONLY | O_EXCL | O_CREAT,0644);
  if(outfd == -1) {
    strerr_die2sys(111,"safecat: fatal: ","couldn't create output file: ");
  }

  /* Step 5:  Copy stdin to the temp file. */
  writefile(outfd);

  /* Close the file, checking the return value. */
  if(fsync(outfd) == -1 || close(outfd) == -1) {
    unlink(tmppath.s);
    strerr_die2sys(111,"safecat: fatal: ","can't fsync/close output file: ");
  }

  /* Step 6:  Link the temp file to its final destination. */
  if(link(tmppath.s,dstpath.s) == -1) {
    unlink(tmppath.s);
    strerr_die2sys(111,"safecat: fatal: ","can't link output file: ");
  }
  /* We've succeeded!  Now, no matter what, we return "success" */

  /* Okay, delete the temporary file. If it fails, bummer. */
  unlink(tmppath.s);

  /* Print the name of the file we've created, as a curtesy. */
  substdio_puts(subfdoutsmall,outfile.s);
  substdio_puts(subfdoutsmall,"\n");
  substdio_flush(subfdoutsmall);
  exit(0);
}
/* ****************************************************************** */
