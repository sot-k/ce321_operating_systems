

PWD := $(shell pwd)

default :
	gcc -Wall -c roots.c
	ar -cvq libroots.a roots.o
	rm roots.o
	gcc -Wall -g find_roots_lib.c -o find_roots_lib -lroots -L$(PWD)
		
	
clean :
	rm -f *.o *.a find_roots_lib
