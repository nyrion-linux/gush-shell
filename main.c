#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

void getUsernameHostname(char *userHostname, size_t size) {
    char *username = getenv("USER");
    char hostname[100];
    gethostname(hostname, sizeof(hostname));

    snprintf(userHostname, size, "%s@%s", username, hostname);
}

void getCurrentDirectory(char *currentDir, size_t size) {
    if (getcwd(currentDir, size) != NULL) {
        printf("Current directory: %s\n", currentDir);
    } else {
        perror("getcwd() error");
    }
}

void execWithChild(char *command, char *args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        // Processo filho
        execvp(command, args);
        exit(1);
    } else if (pid > 0) {
        // Processo pai
        waitpid(pid, NULL, 0);
    } else {
        perror("fork failed");
    }
}

void exitCheck(char *command) {
    if (strcmp(command, "exit") == 0) {
        printf("Exiting shell\n");
        exit(0);
    }
}

void printCommandArguments(char *args[]) {
    int i = 0;
    while (args[i] != NULL) {
        printf("Argument %d: %s\n", i, args[i]);
        i++;
    }
}

void arrayParsedCommand(char *parsedCommand, char *commandArguments[]) {
    int i = 0;
    // Preencher o array de argumentos
    while (parsedCommand != NULL) {
        commandArguments[i] = parsedCommand;
        parsedCommand = strtok(NULL, " ");
        i++;
    }
        commandArguments[i] = NULL; // Finalizar o array com NULL
    }
void parseCmds(char *userCmd) {
    if (userCmd) {
        // Tokenizar o comando do usuário
        char *parsedCommand = strtok(userCmd, " ");
        char *commandArguments[20];
    }
}
int main() {
    char userHostname[100 + 256];
    char currentDir[1024];

    getUsernameHostname(userHostname, sizeof(userHostname));
    getCurrentDirectory(currentDir, sizeof(currentDir));

    printf("Welcome to the shell gush!\n");
    while (1) {
        printf("%s:%s$ ", userHostname, currentDir);

        char *userCommand = readline(NULL);

            // Tokenizar o comando do usuário
            parseCmds(userCommand);
            char *parsedCommand = strtok(userCommand, " ");
            char *commandArguments[20];

            // Preencher o array de argumentos
            arrayParsedCommand(parsedCommand, commandArguments);
            // Verificar se o comando é "exit"
            exitCheck(commandArguments[0]);

            // Criar um processo filho para executar o comando
            execWithChild(commandArguments[0], commandArguments);

        }
    

    return 0;
}