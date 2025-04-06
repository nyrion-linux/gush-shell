#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <limits.h>
#include "historic.h"
#include <linux/limits.h>


// more colors yayayayayaay

#define GRAY    "\x1b[38m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BLACK   "\x1b[30m"
#define WHITE   "\x1b[37m"


void historic_check(int32_t up, int32_t down, const char *userHostname, const char *currentDir) {
    int keyPress = getch();
    if (keyPress == ERR) {
        fprintf(stderr, "Error: getch() failed to read input.\n");
        return;
    }

    char *gushHistoric = getenv("GUSH_HIS_PWD");
    if (gushHistoric == NULL) {
        fprintf(stderr, "Environment variable GUSH_HIS_PWD is not set.\n");
        return;
    }

    FILE *historic_file = fopen(gushHistoric, "r");
    if (historic_file == NULL) {
        perror("Error opening file");
        return;
    }

    // Check if the file is empty
    fseek(historic_file, 0, SEEK_END);
    if (ftell(historic_file) == 0) {
        fprintf(stderr, "DEBUG: .gushistoric file is empty.\n");
        fclose(historic_file);
        return;
    }
    rewind(historic_file);

    if (keyPress == up) { // Handle Up arrow key
        printf("DEBUG: Up arrow key pressed.\n");
        // Logic to display the previous command
        char file_output;
        while (fscanf(historic_file, "%c", &file_output) != EOF) {
            if (file_output == '\n') {
                break;
            } else {
                addch(file_output);
            }
        }
        refresh();
    } else if (keyPress == down) { // Handle Down arrow key
        printf("DEBUG: Down arrow key pressed.\n");
        // Logic to display the next command
        char file_output;
        while (fscanf(historic_file, "%c", &file_output) != EOF) {
            if (file_output == '\n') {
                break;
            } else {
                addch(file_output);
            }
        }
        refresh();
    }

    fclose(historic_file);

    // Redraw the prompt
    printw(GREEN "%s: " RESET, userHostname);
    printw(YELLOW "%s$ " RESET, currentDir);
    refresh();
}

void add_to_historic(char *command) {
    char* gushHistoric = getenv("GUSH_HIS_PWD");
    if (gushHistoric == NULL) {
        fprintf(stderr, "Environment variable GUSH_HIS_PWD is not set.\n");
        return;
    }

    FILE* historic_file = fopen(gushHistoric, "a");
    if (historic_file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(historic_file, "%s\n", command);
    fclose(historic_file);
}

void clear_historic() {
    char* gushHistoric = getenv("GUSH_HIS_PWD");
    if (gushHistoric == NULL) {
        fprintf(stderr, "Environment variable GUSH_HIS_PWD is not set.\n");
        return;
    }

    FILE* historic_file = fopen(gushHistoric, "w");
    if (historic_file == NULL) {
        perror("Error opening file");
        return;
    }
    fclose(historic_file);
}

