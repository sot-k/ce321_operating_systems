#include <sys/syscall.h>
#include <unistd.h>
#include "slob_syscalls_wrapper.h"

long get_total_alloc_mem_syscall_wrapper(void){

	return( syscall(__NR_slob_get_total_alloc_mem) );
}

long get_total_free_mem_syscall_wrapper(void){

	return( syscall(__NR_slob_get_total_free_mem) );
}
