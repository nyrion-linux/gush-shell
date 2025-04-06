#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include "historic.h"
#include <curses.h>
#include <linux/limits.h>
#include <sys/types.h>

// Colors yay yay yay yay yay yay

#define GRAY "\x1b[38m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BLACK "\x1b[30m"
#define WHITE "\x1b[37m"

// RIP colors now spaghetti code no no no no no

int main()
{
    // Initialize the historic file path

    char userHostname[100 + 256];
    char currentDir[1024];

    // Inline code for getUsernameHostname
    char *username = getenv("USER");
    char hostname[100];
    gethostname(hostname, sizeof(hostname));
    snprintf(userHostname, sizeof(userHostname), "%s@%s", username, hostname);

    // Inline code for getCurrentDirectory
    if (getcwd(currentDir, sizeof(currentDir)) != NULL)
    {
        // printf("Current directory: %s\n", currentDir);
    }
    else
    {
        perror("getcwd() error");
    }
    historic_check(KEY_UP, KEY_DOWN, userHostname, currentDir);

    while (1)
    {
        printf(GREEN "%s: " RESET, userHostname);
        printf(YELLOW "%s$ " RESET, currentDir);

        // Read user input
        char *userCommand = readline(NULL);

        if (userCommand && *userCommand)
        {
            // Save the command to the historic file
            add_to_historic(userCommand);

            // Check for the "exit" command
            if (strcmp(userCommand, "exit") == 0)
            {
                free(userCommand);
                printf("Exiting...\n");
                exit(0); // Exit the loop
            }

            pid_t pid = fork();
            if (pid == 0)
            {
                // child

                // Tokenize the command into arguments
                char *commandArguments[256]; // Array to hold arguments
                int i = 0;
                char *token = strtok(userCommand, " ");
                while (token != NULL && i < 255)
                {
                    commandArguments[i++] = token;
                    token = strtok(NULL, " ");
                }
                commandArguments[i] = NULL; // Null-terminate the array

                // Execute the command
                execvp(commandArguments[0], commandArguments);

                // If execvp fails
                perror("Command execution failed");
                exit(1);
            }
            else if (pid < 0)
            {
                // Error forking
                perror("Fork failed");
            }
            else
            {
                // parent
                waitpid(pid, NULL, 0); // Wait for the child process to finish
            }

            // Call historic_check to handle arrow keys
            historic_check(KEY_UP, KEY_DOWN, userHostname, currentDir);
        }

        free(userCommand);
    }

    return 0;
}