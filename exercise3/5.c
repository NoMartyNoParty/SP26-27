#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Error");
		return 2;
	}

	int s = symlink(argv[1], argv[2]);
	if(s == -1){
		perror("Error");
		return 2;
	}

	char buffer[1024];

	int r = readlink(argv[2], buffer, sizeof(buffer));
	if(r == -1){
		perror("Error");
		return 2;
	}

	write(1, buffer, r);
	
	return 0;
}
