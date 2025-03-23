#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char userHostname[100 + 256];
    char currentDir[1024];

    // Inline code for getUsernameHostname
    char *username = getenv("USER");
    char hostname[100];
    gethostname(hostname, sizeof(hostname));
    snprintf(userHostname, sizeof(userHostname), "%s@%s", username, hostname);

    // Inline code for getCurrentDirectory
    if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
        // printf("Current directory: %s\n", currentDir);
    } else {
        perror("getcwd() error");
    }

    printf("Welcome to the shell gush!\n");
    while (1) {
        printf("%s:%s$ ", userHostname, currentDir);

        char *userCommand = readline(NULL);

        if (userCommand) {
            // Inline code for parseCmds and arrayParsedCommand
            char *parsedCommand = strtok(userCommand, " ");
            char *commandArguments[20];
            int i = 0;
            int HasPipe = 0;
            int HasAppendTo = 0;
            int HasWriteTo = 0;
            while (parsedCommand != NULL) {
                commandArguments[i] = parsedCommand;
                parsedCommand = strtok(NULL, " ");
                if (parsedCommand == "|") {
                    HasPipe++;
                }
                if (HasPipe > 5) {
                    printf("\tToo many pipes!\n");
                    break;
                }
                if (parsedCommand == ">>") {
                    HasAppendTo++;
                }
                if (HasAppendTo > 2) {
                    printf("\tToo many Appends!\n");
                    break;
                }
                if (parsedCommand == ">") {
                    HasWriteTo++;
                }
                if (HasWriteTo > 2) {
                    printf("\tToo many Writes!\n");
                    break;
                }
                i++;
            
            }
            commandArguments[i] = NULL; // Finalize the array with NULL

            // Inline code for exitCheck
            if (strcmp(commandArguments[0], "exit") == 0) {
                printf("Exiting shell\n");
                exit(0);
            }

            // Inline code for execWithChild
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                execvp(commandArguments[0], commandArguments);
                exit(1);
            } else if (pid > 0) {
                // Parent process
                waitpid(pid, NULL, 0);
            } else {
                perror("fork failed");
            }
        }
    }

    return 0;
}