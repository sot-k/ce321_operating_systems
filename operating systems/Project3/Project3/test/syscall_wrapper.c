#include <sys/syscall.h>
#include <unistd.h>

#include "syscall_wrapper.h"

long alloc_mem_syscall_wrapper(void) {
	return ( syscall(__NR_slob_get_total_alloc_mem) );
}

long free_mem_syscall_wrapper(void) {
	return( syscall(__NR_slob_get_total_free_mem) );
}
