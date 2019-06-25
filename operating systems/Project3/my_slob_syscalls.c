#include <linux/kernel.h>
#include <linux/syscalls.h>

#include <linux/slob_functions.h>

SYSCALL_DEFINE0(get_total_alloc_mem_syscall){
	
	return(slob_get_total_alloc_mem());
}


SYSCALL_DEFINE0(get_total_free_mem_syscall){

	return(slob_get_total_free_mem());
}
