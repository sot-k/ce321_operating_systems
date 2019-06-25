Georgakidis Christos	1964	cgeorgakidis@uth.gr
Stafylopatis Georgios	2041	gstafylopatis@uth.gr
Karanika Anna		2075	ankaranika@uth.gr

Instructions for test.c compilation:
1)	gcc -c syscall_wrapper.c -o syscall_wrapper.o
2)	ar rcs libmem.a syscall_wrapper.o
3)	gcc -static test.c -L. -lmem -o test



