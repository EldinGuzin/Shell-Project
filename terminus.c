#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

void handle_builtin_commands(char* command) {

    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n')
        command[len - 1] = '\0';

    if (strcmp(command, "exit") == 0) {
        exit(0);
    } 
    
    else if (strcmp(command, "ls") == 0) {
        DIR *dir;
        struct dirent *entry;

        dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening directory");
            return;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (strchr(entry->d_name, '\n') != NULL)
                continue;
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }

    else if (strncmp(command, "touch ", 6) == 0) {
        char* filename = command + 6; 

        FILE* file = fopen(filename, "w");
        if (file != NULL) {
            fclose(file);
            printf("File '%s' created successfully.\n", filename);
        } 
        else {
            perror("Error creating file");
        }
    }

    else if (strncmp(command, "rm ", 3) == 0) {
        char* filename = command + 3; 

        if (unlink(filename) == 0) {
            printf("File '%s' deleted successfully.\n", filename);
        } 
        else {
            perror("Error deleting file");
        }
    }

    else if (strncmp(command, "append ", 7) == 0) {
        char* filename = strtok(command + 7, " "); 
        char* data = strtok(NULL, "\n"); 

        FILE* file = fopen(filename, "a"); 
        if (file != NULL) {
            fprintf(file, "%s\n", data);
            fclose(file);
            printf("Data appended to file '%s' successfully.\n", filename);
        } 
        else {
            perror("Error appending data to file");
        }
    }
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
