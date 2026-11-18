#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error with the number of arguments");
		return 2;
	}

	pid_t p = fork();

	if(p == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		execlp(argv[1], argv[1], NULL);

		perror("Error");
		exit(1);
	}
	else{
		int status;
		wait(&status);

		if(WIFEXITED(status)){
			printf("Process' %s status: %d\n", argv[1], WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}
	return 0;
}

