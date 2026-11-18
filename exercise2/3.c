#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	struct stat file_stat;

	if(argc < 2){
		printf("Not enough arguments");
		return 2;
	}

	for(int i = 0; i < argc; i++){
		printf("Information for %s file", argv[i]);
		
		if(stat(argv[i], &file_stat) == -1){
			perror("Error");
			return 2;
		}
		printf("  Inode number: %lu\n", (unsigned long)file_stat.st_ino); // идентификатор на файла
        	printf("  Size:         %ld bytes\n", (long)file_stat.st_size); // размер в байтове
        	printf("  Blocks (512B):%ld\n", (long)file_stat.st_blocks);     // брой алокирани блокове
        	printf("  Hard links:   %lu\n", (unsigned long)file_stat.st_nlink); // брой твърди връзки

        // Проверяваме какъв е типът на файла чрез POSIX макросите
        	printf("  File type:    ");
        	if (S_ISREG(file_stat.st_mode)) {
            		printf("Regular file\n");
        	} 
		else if (S_ISDIR(file_stat.st_mode)) {
            		printf("Directory\n");
        	} 
		else if (S_ISCHR(file_stat.st_mode)) {
            		printf("Character device\n");
		}
		else if (S_ISBLK(file_stat.st_mode)) {
            		printf("Block device\n");
        	} 
		else if (S_ISFIFO(file_stat.st_mode)) {
            		printf("FIFO/Pipe\n");
        	} 
		else if (S_ISLNK(file_stat.st_mode)) {
            		printf("Symbolic link\n");
        	} 
		else if (S_ISSOCK(file_stat.st_mode)) {
           		printf("Socket\n");
       		} 
		else {
           		printf("Unknown\n");
       		}

       		printf("\n"); // Празен ред за прегледност между файловете
    	}
	return 0;
}
