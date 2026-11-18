#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		for(int i = 0; i < 10; i++){
			char buffer[100];

			int len = sprintf(buffer, "Child: %d", i);

			write(fd, buffer, len);

			sleep(1);
		}
	}
	else{
		for(int i = 0; i < 10; i++){
			char buffer[100];

			int len = sprintf(buffer, "Parent:%d", i);

			write(fd, buffer, len);

			sleep(2);
		}
		wait(NULL);
	}

	close(fd);
	return 0;
}
