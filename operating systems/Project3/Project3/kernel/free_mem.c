#include <linux/kernel.h>
#include <linux/syscalls.h>

#include <linux/slob_functions.h>

SYSCALL_DEFINE0(slob_get_total_free_mem) {
	return(get_total_free_mem());
}
