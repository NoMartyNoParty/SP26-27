#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h> // Задължително за wait() и макросите

int main(int argc, char *argv[]) {
    // Проверяваме дали е подадено поне име на команда (argc трябва да е поне 2)
    if(argc < 2) {
        printf("Not enough arguments\n");
        return 2;
    }

    pid_t p = fork();
    
    if(p == -1) {
        perror("Error fork");
        return 2;
    }

    if(p == 0) {
        // Използваме execvp, защото той приема масив от параметри с неизвестна дължина
        execvp(argv[1], &argv[1]);
        
        perror("Error exec");
        exit(1);
    } 
    else {
        int status;
        wait(&status);
        
        if(WIFEXITED(status)) {
            // Отпечатваме p (PID на детето), а не getpid() (PID на родителя)
            printf("PID: %d, exit status: %d\n", p, WEXITSTATUS(status));
        } else {
            printf("Error: Командата не завърши нормално\n");
        }
    }
    
    return 0;
}
