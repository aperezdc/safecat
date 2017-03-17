/* Copyright (c) 2000, Len Budney. See COPYING for details. */

#include "hostname.h"
#include "stralloc.h"
#include "strerr.h"
#include "tai.h"
#include "taia.h"
#include "fmt.h"
#include <unistd.h>

static
void die_nomem() { strerr_die2x(111,"safecat: fatal: ","out of memory"); }

/* ****************************************************************** */
void mk_tempfile(stralloc *tmpf) {
  char host[256];
  char secbuf[11];
  char atto[TAIA_FMTFRAC];
  char pidbuf[6];
  struct taia now;
  struct tai sec;
  unsigned long int pid = (unsigned long)getpid();

  /* Get a microsecond timestamp with which to build a filename. */
  taia_now(&now);
  taia_tai(&now,&sec);

  /* Record the second timestamp on the string. */
  secbuf[fmt_uint64(secbuf,(uint64_t) sec.x - 4611686018427387904)] = '\0';
  if (!stralloc_cats(tmpf, secbuf)) die_nomem();
  
  /* Append the microsecond timestamp to the string. */
  if (!stralloc_cats(tmpf, ".M")) die_nomem();
  taia_fmtfrac(atto,&now);
  atto[6] = '\0'; /* truncate at microsecond */
  if (!stralloc_cats(tmpf, atto)) die_nomem();

  /* Append the PID to the string. */
  if (!stralloc_append(tmpf, "P")) die_nomem();
  pidbuf[fmt_uint64(pidbuf, pid)] = '\0';
  if (!stralloc_cats(tmpf, pidbuf)) die_nomem();
  
  /* Copy the hostname to the buffer. */
  if (!stralloc_append(tmpf, ".")) die_nomem();
  get_hostname(host,sizeof(host));
  if (!stralloc_cats(tmpf, host)) die_nomem();
  if (!stralloc_0(tmpf)) die_nomem();
}
/* ****************************************************************** */


