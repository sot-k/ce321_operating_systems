#include <stdio.h>
#define N 200

int main(int argc, char *argv[]) {
	FILE *fd;
	int num,i;

	fd = fopen("/media/test_disk/testFile.txt", "r+");
	
	for (i=0; i < N; i+=2) {
		fseek(fd, (N-i)*1024*1024, SEEK_SET);
		fscanf(fd," %d", &num);
		fseek(fd, (N-i)*1024*1024, SEEK_SET);
		num +=i;
		fprintf(fd,"%d",num);		
	}
	fflush(fd);
	return (0);
}
