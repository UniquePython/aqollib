#include "memory/safe.h"
#include "errors/error.h"

#include <stdlib.h>

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
