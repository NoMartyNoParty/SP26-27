#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

int main(int argc, char *argv[]){
	int fd;

	if(argc != 2){
		printf("Error");
		return 2;
	}

	struct utimbuf time;
	struct stat file_stat;

	if(stat(argv[1], &file_stat) == -1){
		perror("Error");
		return 2;
	}
		
	time.actime = file_stat.st_atime - 3600;
	time.modtime = file_stat.st_mtime + 60;
	
	if(utime(argv[1], &time) == -1){
		perror("Error");
		return 2;
	}

	return 0;
}

