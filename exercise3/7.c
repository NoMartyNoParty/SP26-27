#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error");
		return 2;
	}

	if(chdir(argv[1]) == -1){
		perror("Cannot change directory");
		return 2;
	}
	
	return 0;
}
