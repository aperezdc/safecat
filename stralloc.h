#ifndef STRALLOC_H
#define STRALLOC_H

#include "gen_alloc.h"

GEN_ALLOC_typedef(stralloc,char,s,len,a)

extern int stralloc_ready();
extern int stralloc_readyplus();
extern int stralloc_copy();
extern int stralloc_cat();
extern int stralloc_copys();
extern int stralloc_cats();
extern int stralloc_copyb();
extern int stralloc_catb();
extern int stralloc_append(); /* beware: this takes a pointer to 1 char */
extern int stralloc_starts();

#define stralloc_0(sa) stralloc_append(sa,"")

extern int stralloc_catulong0();
extern int stralloc_catlong0();

#define stralloc_catlong(sa,l) (stralloc_catlong0((sa),(l),0))
#define stralloc_catuint0(sa,i,n) (stralloc_catulong0((sa),(unsigned long) (i),(n)))
#define stralloc_catint0(sa,i,n) (stralloc_catlong0((sa),(long) (i),(n)))
#define stralloc_catint(sa,i) (stralloc_catlong0((sa),(long) (i),0))

#endif
