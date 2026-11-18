#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc < 5){
		printf("Not enough arguments");
		return 2;
	}

	int fd1 = open(argv[argc-3], O_RDONLY);
	if(fd1 == -1){
		perror("Error");
		return 2;
	}

	int fd2 = open(argv[argc-2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd2 == -1){
		perror("Error");
		return 2;
	}

	int fd3 = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd3 == -1){
		perror("Error");
		return 2;
	}

	pid_t p = fork();
	if(p == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		dup2(fd1, 0);
		dup2(fd2, 1);
		dup2(fd3, 2);

		close(fd1);
		close(fd2);
		close(fd3);

		for(int i = argc-3; i < argc; i++){
			argv[i] = NULL;
		}

		execvp(argv[1], &argv[1]);

		perror("Error");
		exit(1);
	}
	else{
		int status;
		wait(&status);

		if(WIFEXITED(status)){
			printf("Exit status: %d", WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}
	
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}
