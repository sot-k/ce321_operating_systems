#include "syscall_wrapper.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	
	printf("Allocated Memory: %ld\nFree Memory: %ld\n", alloc_mem_syscall_wrapper(), free_mem_syscall_wrapper());
	
	return 0;
}
