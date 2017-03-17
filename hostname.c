/* Copyright (c) 2000, Len Budney. See COPYING for details. */
#include "hostname.h"
#include "strerr.h"
#include <unistd.h>

/* ****************************************************************** */
void get_hostname(char *hostnam, size_t len) {
  if(gethostname(hostnam, len) == 0) return;

  /* Fatal error if we can't read the hostname. */
  strerr_die1sys(111, "safecat: fatal: can't determine hostname: ");
}
/* ****************************************************************** */
