#include "syscall_wrapper.h"
#include <stdio.h>

int main (int argc, char *argv[]){
	printf("Allocated Memory: %ld.\n Free Memory: %ld.\n", alloc_mem_syscall_wrapper(), free_mem_syscall_wrapper())
}

