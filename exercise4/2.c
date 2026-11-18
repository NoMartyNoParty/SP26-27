#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	printf("Process ID:%d\n", getpid());

	pid_t child = fork();

	if(child == -1){
		perror("Error");
		return 2;
	}

	if(child == 0){
		printf("Child's ID: %d; PID: %d; Parent's PID: %d", child, getpid(),getppid());
		exit(7);
	}
	else{
		printf("PPID: %d, PID: %d", child, getpid());

		int status;
		wait(&status);

		if(WIFEXITED(status)){
			printf("Child's status: %d\n", WEXITSTATUS(status));
		}
		else{
			printf("Error");
		}
	}
	
	return 0;
}
