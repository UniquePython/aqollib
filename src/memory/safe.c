#include "memory/safe.h"
#include "errors/error.h"

#include <stdlib.h>

size_t GetTypeSize(DType dtype)
{
    size_t type_size;
    switch (dtype)
    {
    case INT:
        type_size = sizeof(int);
        break;
    case DOUBLE:
        type_size = sizeof(double);
        break;
    case FLOAT:
        type_size = sizeof(float);
        break;
    case CHAR:
        type_size = sizeof(char);
        break;
    default:
        type_size = 1;
        break;
    }

    return type_size;
}

void *SafeMalloc(DType dtype, size_t nmemb)
{
    void *out = malloc(nmemb * GetTypeSize(dtype));
    HANDLE_NULL_PTR(out, "SafeMalloc failed: out of memory!");
    return out;
}

void *SafeCalloc(DType dtype, size_t nmemb)
{
    void *out = calloc(nmemb, GetTypeSize(dtype));
    HANDLE_NULL_PTR(out, "SafeCalloc failed: out of memory!");
    return out;
}

void *SafeRealloc(DType dtype, void *ptr, size_t nmemb)
{
    void *out = realloc(ptr, nmemb * GetTypeSize(dtype));
    HANDLE_NULL_PTR(out, "SafeRealloc failed: out of memory!");
    return out;
}
