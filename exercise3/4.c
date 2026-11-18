#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	
	if(argc != 3){
		printf("Error");
		return 2;
	}

	int l = link(argv[1], argv[2]);
	if(l == -1){
		perror("Error");
		return 2;
	}

	int u = unlink(argv[1]);
	if(u == -1){
		perror("Error");
		return 2;
	}

	return 0;
}
	
