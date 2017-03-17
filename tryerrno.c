#include <errno.h>

void main() {
  errno = 0;
  _exit(errno);
}
