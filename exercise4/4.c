#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Not 3 arguments");
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

	pid_t f = fork();
	if(f == -1){
		perror("Error");
		return 2;
	}

	if(f == 0){
		execlp(argv[2], argv[2], NULL);
		
		perror("Error");
		exit(1);
	}

	for(int i = 0; i < 2; i++){

		int status;
		pid_t finishedprocess = wait(&status);

		char *process;
		if(finishedprocess == p){
			process = argv[1];
		}
		else{
			process = argv[2];
		}

		if(WIFEXITED(status)){
			printf("Process: %s; Status: %d\n", process, WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}
	
	return 0;
}

