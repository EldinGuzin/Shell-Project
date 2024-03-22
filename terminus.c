#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

void penguin();

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
    else if (strncmp(command, "cat ", 4) == 0) {
       
        char* filename = command + 4; 
        size_t filename_len = strlen(filename);
        if (filename_len > 0 && filename[filename_len - 1] == '\n')
            filename[filename_len - 1] = '\0';

        printf("Opening file: %s\n", filename); 

        FILE* file = fopen(filename, "r");
        if (file != NULL) {
            int c;
            while ((c = fgetc(file)) != EOF) {
                putchar(c);
            }
            fclose(file);
        } 
        else {
            perror("Error opening file");
        }
    }

    else if (strncmp(command, "cowsay ", 7) == 0) {
        char* message = command + 7;
        char cowsay_command[100];
        sprintf(cowsay_command, "cowsay \"%s\"", message);
        system(cowsay_command);
    }

    else if (strcmp(command, "clear") == 0) {
        system("clear"); 
    }
    else if (strcmp(command, "penguin") == 0) {
        penguin(); 
    }
    else {
        printf("Invalid command: %s\n", command);
    }
}

void penguin() {
    printf("        .--.      \n");
    printf("       |o_o |     \n");
    printf("       |:_/ |     \n");
    printf("      //   \\ \\    \n");
    printf("     (|     | )   \n");
    printf("    /'\\_   _/`\\   \n");
    printf("    \\___)=(___/   \n");
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
