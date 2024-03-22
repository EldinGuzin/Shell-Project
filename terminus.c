#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

int handle_builtin_commands(char* command) {

    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n')
        command[len - 1] = '\0';

    if (strcmp(command, "exit") == 0) {
        exit(0);
    } 
    
    return 0;
}

int main() {
    char input[100];
    char hostname[1024];
    gethostname(hostname, sizeof(hostname)); 

    while (1) {
        printf("\033[1;35m%s$\033[0m ", hostname);
        fgets(input, sizeof(input), stdin); 

        handle_builtin_commands(input);

    }

    return 0;
}
