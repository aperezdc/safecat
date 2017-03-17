#include "fmt.h"
#include <stdint.h>

unsigned int fmt_uint64(s,u) register char *s; register uint64_t u;
{
  register unsigned int len; register uint64_t q;
  len = 1; q = u;
  while (q > 9) { ++len; q /= 10; }
  if (s) {
    s += len;
    do { *--s = '0' + (u % 10); u /= 10; } while(u); /* handles u == 0 */
  }
  return len;
}
