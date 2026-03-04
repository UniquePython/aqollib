#include "io/stdin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *ReadLine(FILE *stream)
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t len = getline(&line, &cap, stream);

    if (len == -1)
    {
        free(line);
        return NULL;
    }

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    return line;
}

char *ReadLinePrompt(const char *prompt)
{
    fputs(prompt, stdout);
    fflush(stdout);
    return ReadLine(stdin);
}