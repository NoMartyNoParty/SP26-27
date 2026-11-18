#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd1;

	fd1 = open("first.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(fd1 == -1){
		perror("Cannot create file");
		return 2;
	}
	close(fd1);

	mode_t old_mask = umask(0022);

	int fd2 = open("second.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(fd2 == -1){
		perror("Cannot create and open second file");
		return 2;
	}
	close(fd2);

	umask(old_mask);
	printf("The program has ended, check the file rights using ls -l ...");

	return 0;
}

