#ifndef HISTORIC_H
#define HISTORIC_H

#include <stdint.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void historic_check(int32_t up, int32_t down, const char *userHostname, const char *currentDir);
void add_to_historic(char *command);
void clear_historic();

#endif // HISTORIC_H