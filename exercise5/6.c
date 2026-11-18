#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Not enough arguments");
		return 2;
	}

	pid_t p = fork();
	if(p == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		execvp(argv[1], &argv[1]);

		perror("Error");
		exit(1);
	}
	else{
		int status;
		wait(&status);

		if(WIFEXITED(status)){
			printf("PID: %d, PPID: %d, exit status: %d)", getpid(), getppid(), WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}
	return 0;
}
	
