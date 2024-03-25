#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        
        printf("Child process started\n");
        printf("Child process ID: %d\n", getpid());
        printf("Executing ls command...\n");
        
        char *args[] = {"ls", NULL};
        execv("/bin/ls", args);
        
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        
        printf("Parent process started\n");
        printf("Parent process ID: %d\n", getpid());
        printf("Sending SIGTERM signal to the child process\n");
        
        // Wait for a moment
        sleep(2);
        
        if (kill(pid, SIGTERM) == -1) {
            perror("Kill failed");
            exit(EXIT_FAILURE);
        }
        printf("Signal sent\n");
        
        wait(NULL);
        printf("Child process terminated\n");
    }
    return 0;
}
