#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fd;
	int num,i;

	fd = fopen("/media/test_disk/testFile.txt", "w+");
	for (i = 1; i <= 200*1024*1024; i++) {
		num = i;
		fprintf(fd, "%d", num);
		
	}

	return (0);
}
