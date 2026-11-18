#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t n_read;
	char buffer;
	int lines = 0, words = 0, bytes = 0;

	if(argc != 2){
		printf("Not 2 arguments");
		return 2;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("Cannot open file");
		return 2;
	}

	while(1){
		n_read = read(fd, &buffer, sizeof(buffer));

		if(n_read == -1){
			perror("Cannot read");
			close(fd);
			return 2;
		}

		if(n_read == 0){
			break;
		}

		if(buffer == '\n'){
			lines++;
		}
		
		else if(buffer == '\t'){
			words++;
		}
		
		bytes++;
	}

	printf("Lines: %d, words: %d, bytes: %d", lines, words, bytes);
	close(fd);
	return 0;
}
