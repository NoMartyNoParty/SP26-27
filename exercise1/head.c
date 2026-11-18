#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t n_read;
	char buffer;
	int lines = 0;

	if(argc != 2){
		printf("Not 2 arguments");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("Cannot open file");
		return 2;
	}

	while((n_read = read(fd, &buffer, sizeof(buffer))) > 0){
		if(write(1, &buffer, n_read) != n_read){
			perror("Error");
			close(fd);
			return 3;
		}

		if(buffer == '\n'){
			lines++;
			if(lines == 10){
				break;
			}
		}
	}

	close(fd);

	return 0;
}
