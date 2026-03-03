#include "memory/free.h"

#include <stdlib.h>
#include <stdarg.h>

void FreePtr(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

void FreeAll(size_t count, ...)
{
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; i++)
    {
        void **ptr = va_arg(args, void **);
        FreePtr(ptr);
    }

    va_end(args);
}