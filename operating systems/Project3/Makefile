
PWD := $(shell pwd)

default :
  gcc -Wall -c slob_syscalls_wrapper.c
  ar -cvq libslob_syscalls_wrapper.a slob_syscalls_wrapper.o
	rm slob_syscalls_wrapper.o
  gcc -Wall -g test.c -o test -lslob_syscalls_wrapper -L$(PWD)

  clean :
  	rm -f *.o *.a test
