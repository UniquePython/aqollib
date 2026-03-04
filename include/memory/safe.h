#ifndef SAFE_H
#define SAFE_H

#include <stdlib.h>

#include "dtype/dtype.h"

size_t GetTypeSize(DType dtype);

void *SafeMalloc(DType dtype, size_t nmemb);
void *SafeCalloc(DType dtype, size_t nmemb);
void *SafeRealloc(DType dtype, void *ptr, size_t nmemb);

#define MALLOC_INT(nmemb) (int *)SafeMalloc(INT, nmemb)
#define MALLOC_LONG(nmemb) (long *)SafeMalloc(LONG, nmemb)
#define MALLOC_LONG_LONG(nmemb) (long long *)SafeMalloc(LONG_LONG, nmemb)
#define MALLOC_SHORT(nmemb) (short *)SafeMalloc(SHORT, nmemb)
#define MALLOC_UINT(nmemb) (unsigned int *)SafeMalloc(UNSIGNED_INT, nmemb)
#define MALLOC_UCHAR(nmemb) (unsigned char *)SafeMalloc(UNSIGNED_CHAR, nmemb)
#define MALLOC_SIZE_T(nmemb) (size_t *)SafeMalloc(SIZE_T, nmemb)
#define MALLOC_DOUBLE(nmemb) (double *)SafeMalloc(DOUBLE, nmemb)
#define MALLOC_FLOAT(nmemb) (float *)SafeMalloc(FLOAT, nmemb)
#define MALLOC_CHAR(nmemb) (char *)SafeMalloc(CHAR, nmemb)

#define CALLOC_INT(nmemb) (int *)SafeCalloc(INT, nmemb)
#define CALLOC_LONG(nmemb) (long *)SafeCalloc(LONG, nmemb)
#define CALLOC_LONG_LONG(nmemb) (long long *)SafeCalloc(LONG_LONG, nmemb)
#define CALLOC_SHORT(nmemb) (short *)SafeCalloc(SHORT, nmemb)
#define CALLOC_UINT(nmemb) (unsigned int *)SafeCalloc(UNSIGNED_INT, nmemb)
#define CALLOC_UCHAR(nmemb) (unsigned char *)SafeCalloc(UNSIGNED_CHAR, nmemb)
#define CALLOC_SIZE_T(nmemb) (size_t *)SafeCalloc(SIZE_T, nmemb)
#define CALLOC_DOUBLE(nmemb) (double *)SafeCalloc(DOUBLE, nmemb)
#define CALLOC_FLOAT(nmemb) (float *)SafeCalloc(FLOAT, nmemb)
#define CALLOC_CHAR(nmemb) (char *)SafeCalloc(CHAR, nmemb)

#define REALLOC_INT(ptr, nmemb) (int *)SafeRealloc(INT, ptr, nmemb)
#define REALLOC_LONG(ptr, nmemb) (long *)SafeRealloc(LONG, ptr, nmemb)
#define REALLOC_LONG_LONG(ptr, nmemb) (long long *)SafeRealloc(LONG_LONG, ptr, nmemb)
#define REALLOC_SHORT(ptr, nmemb) (short *)SafeRealloc(SHORT, ptr, nmemb)
#define REALLOC_UINT(ptr, nmemb) (unsigned int *)SafeRealloc(UNSIGNED_INT, ptr, nmemb)
#define REALLOC_UCHAR(ptr, nmemb) (unsigned char *)SafeRealloc(UNSIGNED_CHAR, ptr, nmemb)
#define REALLOC_SIZE_T(ptr, nmemb) (size_t *)SafeRealloc(SIZE_T, ptr, nmemb)
#define REALLOC_DOUBLE(ptr, nmemb) (double *)SafeRealloc(DOUBLE, ptr, nmemb)
#define REALLOC_FLOAT(ptr, nmemb) (float *)SafeRealloc(FLOAT, ptr, nmemb)
#define REALLOC_CHAR(ptr, nmemb) (char *)SafeRealloc(CHAR, ptr, nmemb)

#endif