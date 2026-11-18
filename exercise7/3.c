#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int fd[2];

	if(pipe(fd) == -1){
		perror("Error");
		return 2;
	}

	write(fd[1], "Some test text here", 17);

 	char buffer[100];
	ssize_t n_read = read(fd[0], buffer, sizeof(buffer));

	write(1, buffer, n_read);

	close(fd[0]);
	close(fd[1]);
	return 0;
}
