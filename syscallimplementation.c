#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    
    pid_t pid = fork();
    if (pid < 0) {
        
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
      
        char *args[] = {"neofetch", NULL};
        execvp(args[0], args);
        
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {

        wait(NULL);
        printf("Child process completed\n");
        
    }
    return 0;
}


