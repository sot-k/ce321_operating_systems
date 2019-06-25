#include <linux/kernel.h>
#include <linux/syscalls.h>

#include <linux/slob_functions.h>

SYSCALL_DEFINE0(slob_get_total_alloc_mem) {
	long val = get_total_alloc_mem();
	return(val);
}
