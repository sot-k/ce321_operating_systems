#include <sys/syscall.h>
#include <unistd.h>
#include "roots.h"


long find_roots_wrapper (void) {
  return( syscall(__NR_find_roots) );
}
