#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd1 = open("test.txt", O_RDONLY);
	if(fd1 == -1){
		perror("Error");
		return 2;
	}

	int fd2 = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd2 == -1){
		perror("Error");
		return 2;
	}

	pid_t p = fork();
	if(p == -1){
		perror("Error");
		return 2;
	}

	if(p == 0){
		for(int i = 0; i < 100; i++){
			char buffer[100];

			int len = sprintf(buffer, "Child: %d", i);

			write(fd2, buffer, len);

			sleep(2);
		}
	}
	else{
		ssize_t n_read;
		for(int i = 0; i < 100; i++){
			char buffer[100];

			n_read = read(fd1, buffer, 10);

			if(n_read == -1){
				perror("Error");
				return 2;
			}

			if(n_read == 0){
				break;
			}
			
			write(fd2, buffer, n_read);
			
			sleep(1);
		}
		wait(NULL);
	}
	close(fd1);
	close(fd2);
	return 0;
}	
