#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	ssize_t n_read1, n_read2;
	char buffer1, buffer2;

	if(argc != 4){
		printf("Not 4 arguments");
		return 2;
	}

	fd1 = open(argv[2], O_RDONLY);
	if(fd1 == -1){
		perror("Cannot open file");
		return 2;
	}

	fd2 = open(argv[3], O_RDONLY);
	if(fd2 == -1){
		perror("Cannot open file");
		close(fd1);
		return 2;
	}

	while(1){
		n_read1 = read(fd1, &buffer1, sizeof(buffer1));
		n_read2 = read(fd2, &buffer2, sizeof(buffer2));

		if(n_read1 == -1 || n_read2 == -1){
			perror("Error while reading");
			close(fd1);
			close(fd2);
			return 2;
		}

		if(n_read1 == 0 && n_read2 == 0){
			printf("Success");
			break;
		}

		if(n_read1 != n_read2 || buffer1 != buffer2){
			perror("Not the same");
			close(fd1);
			close(fd2);
			return 1;
		}
	}

	printf("The files are the same and have the same content");
	close(fd1);
	close(fd2);

	return 0;
}
