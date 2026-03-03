#ifndef FREE_H
#define FREE_H

#include <stddef.h>

void FreePtr(void **ptr);

void FreeAll(size_t count, ...);

#define FREE_ALL(...) \
    FreeAll(sizeof((void *[]){__VA_ARGS__}) / sizeof(void *), __VA_ARGS__)

#endif