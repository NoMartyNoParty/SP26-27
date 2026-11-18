#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t n_read;
	char buffer;
	int lines = 0;

	if(argc != 2){
		printf("Not 2 arguments");
		return 2; 
	}

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("Cannot open file");
		return 2;
	}

	off_t position = lseek(fd, 0, SEEK_END);
	if(position == -1){
		perror("Error");
		close(fd);
		return 2;
	}

	if(position > 0){
		position = lseek(fd, -2, SEEK_END);
	}

	while(position >= 0){
		if(read(fd, &buffer, 1) != 1){
			perror("Error");
			close(fd);
			return 2;
		}

		if(buffer == '\n'){
			lines++;
			if(lines == 10){
				break;
			}
		}
	
		if(position == 0){
			lseek(fd, 0, SEEK_SET);
			break;
		}

		position = lseek(fd, -2, SEEK_CUR);
	}

	while((n_read = read(fd, &buffer, sizeof(buffer))) > 0){
		if(write(1, &buffer, n_read) != n_read){
			perror("Error");
			close(fd);
			return 2;
		}
	}

	close(fd);
	return 0;
}
