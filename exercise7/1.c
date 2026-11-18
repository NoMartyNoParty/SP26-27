#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int fd[2];

	if(pipe(fd) == -1){
		perror("Error");
		return 2;
	}

	close(fd[1]);

	char buffer[100];

	ssize_t n_read = read(fd[0], buffer, sizeof(buffer));

	close(fd[0]);

	return 0;
}
