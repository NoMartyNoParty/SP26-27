#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd1;
	char buffer; 

	fd1 = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd1 == -1){
		printf("Cannot open file");
		return 2;
	}

	close(1);

	dup(fd1);

	close(fd1);

	write(1, "This will go to the file\n", 25);
	printf("This will ALSO go to the file\n");

	return 0;
} 	
