#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    	if (mkdir("newdir", 0777) == -1) {
        	perror("Error mkdir");
        	return 2;
    	}

      	if (chdir("newdir") == -1) {
        	perror("Error chdir");
        	return 2;
    	}

    	if (symlink("does_not_exist.txt", "my_link") == -1) {
        	perror("Error symlink");
        	return 2;
    	}

    	if (unlink("my_link") == -1) {
        	perror("Error unlink");
        	return 2;
    	}	

    	if (chdir("..") == -1) {
        	perror("Error chdir ..");
        	return 2;
    	}

       	if (rmdir("newdir") == -1) {
        	perror("Error rmdir");
        	return 2;
    	}

    	printf("Успешно изпълнени всички стъпки!\n");
	return 0;
}
	
