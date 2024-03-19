#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_builtin_commands(char* command) {
    if (strcmp(command, "exit\n") == 0) {
        exit(0);
    } 
    
    return 0;
}

int main() {
    char input[100]; 

    while (1) {
        printf("$ "); 
        fgets(input, sizeof(input), stdin); 

        handle_builtin_commands(input);

    }

    return 0;
}
