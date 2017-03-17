#include "config.h"
#include "strcat_alloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ****************************************************************** */
char *strcat_alloc(const char *path,const char *filename) {
  /* Allocate a pointer to return. */
  char *retval = (char *)malloc(strlen(path) + strlen(filename) + 2);
  if(retval == NULL) {
    fprintf(stderr, "Could not allocate memory.\n");
    exit(1);
  }

  /* Copy the path and filename to the destination string. */
  memcpy(retval,path,strlen(path));
  if(retval[strlen(path)] != '/') {
    retval[strlen(path)] = '/';
    retval[strlen(path) + 1] = '\0';
  }

  /* Append the temp filename to our new strings. */
  strcat(retval,filename);
  return(retval);
}
/* ****************************************************************** */
