#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char buffer;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = dup(fd1);
	
	if(read(fd1, &buffer, 1) > 0){
		write(1, &buffer, 1);
	}

	if(read(fd2, &buffer, 1) > 0){
		write(1, &buffer, 1);
	}

	close(fd1);

	if(read(fd2, &buffer, 1) > 0){
		write(1, &buffer, 1);
	}
	
	close(fd2);

	return 0;
}
