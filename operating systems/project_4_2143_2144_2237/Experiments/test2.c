#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fd;
	int num,i,j;
	
	fd = fopen("/media/test_disk/testFile.txt", "r+");
	
	num=0;
	for (i = 0; i < 40; i++) 
	{
		if (i%5 == 0) 
		{
			fseek(fd, i*1024*1024*10, SEEK_SET);
			fprintf(fd, "%d", num);
			continue;
		}
		else
		{
			fseek(fd, i*1024*1024*10, SEEK_SET);
			for (j=0; j<100; j++) {
				num = j;
				fprintf(fd, "%d", num);
				fseek(fd, -1, SEEK_CUR);
			}
		}	
	}
	fflush(fd);
	return (0);
}
