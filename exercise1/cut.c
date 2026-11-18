#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t n_read;
	char buffer;
	int m = 0, n = 0;
	int cur_pos = 0;

	if(argc != 2){ 
		printf("Error");
		return 2;
	}

	if(scanf("%d, %d", &m, &n) != 2 || m < 0 || n < m){
		perror("Error");
		return 2;
	}

	fd = open(argv[4], O_RDONLY);
	if(fd == -1){
		perror("Cannot open file");
		return 2;
	}
	
	while((n_read = read(fd, &buffer, 1)) > 0){
		if(buffer == '\n'){
			write(1, &buffer, 1);
			cur_pos = 0;
		}
	
		else{
			cur_pos++;
		}

		if(cur_pos >= m && cur_pos <= n){
			if(write(1, &buffer, 1) != 1){
				perror("Error");
				close(fd);
				return 2;
			}
		}
	}

	close(fd);

	return 0;
}
