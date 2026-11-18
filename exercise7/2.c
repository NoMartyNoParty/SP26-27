#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int fd[2];

	if(pipe(fd) == -1){
		perror("Error");
		return 2;
	}

	close(fd[0]);

	write(fd[0], "Test text here!", 14);

	close(fd[1]);
	return 0;
}
