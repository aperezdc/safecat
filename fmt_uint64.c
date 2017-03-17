#include "fmt.h"
#include "uint64.h"

unsigned int fmt_uint64(s,u) register char *s; register uint64 u;
{
  register unsigned int len; register uint64 q;
  len = 1; q = u;
  while (q > 9) { ++len; q /= 10; }
  if (s) {
    s += len;
    do { *--s = '0' + (u % 10); u /= 10; } while(u); /* handles u == 0 */
  }
  return len;
}
