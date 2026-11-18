#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	
	struct stat file_stat;

	if(argc < 2){
		printf("Not enough aguments");
		return 2;
	}

	for(int i = 0; i < argc; i++){
		if(stat(argv[i], &file_stat) == -1){
			perror("Error, missing file");
			continue;
		}

		mode_t current = file_stat.st_mode;

		mode_t new_mode = (current | S_IWGRP) & ~S_IXOTH;

		int mode = chmod(argv[i], new_mode);
		if(mode == -1){
			perror("Error");
			return 2;
		}
	}

	return 0;
}
		

