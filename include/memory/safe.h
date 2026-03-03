#ifndef SAFE_H
#define SAFE_H

#include <stdlib.h>

typedef enum e_dtype
{
    INT,
    DOUBLE,
    FLOAT,
    CHAR
} DType;

size_t GetTypeSize(DType dtype);

void *SafeMalloc(DType dtype, size_t nmemb);
void *SafeCalloc(DType dtype, size_t nmemb);
void *SafeRealloc(DType dtype, void *ptr, size_t nmemb);

#define MALLOC_INT(nmemb) (int *)SafeMalloc(INT, nmemb)
#define MALLOC_DOUBLE(nmemb) (double *)SafeMalloc(DOUBLE, nmemb)
#define MALLOC_FLOAT(nmemb) (float *)SafeMalloc(FLOAT, nmemb)
#define MALLOC_CHAR(nmemb) (char *)SafeMalloc(CHAR, nmemb)

#define CALLOC_INT(nmemb) (int *)SafeCalloc(INT, nmemb)
#define CALLOC_DOUBLE(nmemb) (double *)SafeCalloc(DOUBLE, nmemb)
#define CALLOC_FLOAT(nmemb) (float *)SafeCalloc(FLOAT, nmemb)
#define CALLOC_CHAR(nmemb) (char *)SafeCalloc(CHAR, nmemb)

#define REALLOC_INT(ptr, nmemb) (int *)SafeRealloc(INT, ptr, nmemb)
#define REALLOC_DOUBLE(ptr, nmemb) (double *)SafeRealloc(DOUBLE, ptr, nmemb)
#define REALLOC_FLOAT(ptr, nmemb) (float *)SafeRealloc(FLOAT, ptr, nmemb)
#define REALLOC_CHAR(ptr, nmemb) (char *)SafeRealloc(CHAR, ptr, nmemb)

#endif