#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	printf("Process ID: %d", getpid());
	printf("\nParent's process ID: %d", getppid());

	execlp("ps", "ps", NULL);


	perror("Error trying to change the obraz");

	return 0;
}
