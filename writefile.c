/* Copyright (c) 2017, Adrian Perez de Castro <aperez@igalia.com> */
/* Copyright (c) 2000, Len Budney. See COPYING for details. */
#include "stralloc.h"
#include "strerr.h"
#include "subfd.h"
#include "substdio.h"
#include "writefile.h"
#include <errno.h>
#include <unistd.h>

extern stralloc tmppath;

/* ****************************************************************** */
void writefile(int fd) {
  char inbuf[512];
  char outbuf[512];
  substdio ssin;
  substdio ssout;

  /* Prepare substdio buffers for reading and writing. */
  substdio_fdbuf(&ssin,read,0,inbuf,sizeof(inbuf));
  substdio_fdbuf(&ssout,write,fd,outbuf,sizeof(outbuf));

  /* Copy stdin to the output file, watching the return values each time. */
  if (substdio_copy(&ssout,&ssin) < 0) goto fail;
  if (substdio_flush(&ssout) == -1) goto fail;

  /* The file is copied. */
  return;

 fail:
  unlink(tmppath.s);
  strerr_die2x(111,"safecat: fatal: ","unable to copy standard input");
}
/* ****************************************************************** */
