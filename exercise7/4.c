#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2];

	if(pipe(fd) == -1){
		perror("Error");
		return 2;
	}

	pid_t p = fork();
	if(p == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		char buffer[100];

		ssize_t n_read = read(fd[0], buffer, sizeof(buffer));

		while(n_read > 0){
			if(write(1, buffer, n_read) != n_read){
				perror("Error");
				return 2;
			}
		}
		close(fd[0]);
	}
	else{
		close(fd[0]);

		int status;

		for(int i = 0; i < argc; i++){
			write(fd[1], argv[i], strlen(argv[i]));
			sleep(1);
		}

		close(fd[1]);
	
		wait(&status);
	}
	
	return 0;
}
