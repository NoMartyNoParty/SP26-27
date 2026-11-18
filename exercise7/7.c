#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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
		
		
		pid_t f = fork();
		if(f == -1){
			perror("Error");
			return 2;
		}
		
		if(f == 0){
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);

			execlp(argv[1], argv[1], NULL);

			perror("Error");
			exit(1);
		}

		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);

		execlp(argv[2], argv[2], NULL);

		perror("Error");
		exit(1);
	}

	wait(NULL);

	return 0;
}
