#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int fd1[2], fd2[2];

	if(pipe(fd1) == -1){
		perror("Error");
		return 2;
	}

	if(pipe(fd2) == -1){
		perror("Error");
		return 2;
	}

	pid_t p = fork();
	if(p == -1){
		perror("Error");
		return 2;
	}

	pid_t f = fork();
	if(f == -1){
		perror("Error");
		return 2;
	}

	pid_t t = fork();
	if(t == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		
		dup2(fd1[1], 1);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);

		execlp(argv[1], argv[1], NULL);

		perror("Error");
		exit(1);
	}

	if(f == 0){
		dup2(fd1[0], 0);
		dup2(fd2[1], 1);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);

		execlp(argv[2], argv[2], NULL);

		perror("Error");
		exit(1);
	}

	if(t == 0){
		dup2(fd2[0], 0);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);

		execlp(argv[3], argv[3], NULL);

		perror("Error");
		exit(1);
	}

	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	return 0;
}
