#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Not enough arguments");
		return 2;
	}

	int fd = open(argv[argc-1], O_WRONLY | O_APPEND);
	if(fd == -1){
		perror("Error");
		return 2;
	}

	pid_t p = fork();

	if(p == -1){
		perror("Error");
		return 2;
	}
	
	if(p == 0){
		dup2(fd, 1);

		close(fd);

		argv[argc-1] = NULL;

		execvp(argv[1], &argv[1]);

		perror("Error");
		exit(1);
	}
	else{
		int status;
		wait(&status);

		if(WIFEXITED(status)){
			printf("PID: %d, exit status: %d", getpid(), WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}

	close(fd);
	return 0;
}
