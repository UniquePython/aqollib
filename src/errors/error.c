#include "errors/error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void HandleNullPtr(void *ptr, const char *errormsg, bool fatal, const char *file, int line)
{
    if (!ptr)
    {
        if (fatal)
        {
            fprintf(stderr, "[ERROR] %s (at %s:%d)\n", errormsg, file, line);
            exit(EXIT_FAILURE);
        }
        else
            fprintf(stderr, "[WARNING] %s (at %s:%d)\n", errormsg, file, line);
    }
}

void HandleNonZeroReturn(int retval, const char *errormsg, bool fatal, const char *file, int line)
{
    if (retval != 0)
    {
        if (fatal)
        {
            fprintf(stderr, "[ERROR] %s (at %s:%d)\n", errormsg, file, line);
            exit(EXIT_FAILURE);
        }
        else
            fprintf(stderr, "[WARNING] %s (at %s:%d)\n", errormsg, file, line);
    }
}
