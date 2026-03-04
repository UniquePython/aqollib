#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdbool.h>

#include "dtype/dtype.h"

typedef struct
{
    void *data;
    DType dtype;
    size_t length;
    size_t capacity;
    bool owned;
} Array;

Array *ArrayCreate(DType dtype, size_t capacity);
Array *ArrayFrom(DType dtype, void *data, size_t length);
void ArrayDestroy(Array **arr);

void ArrayPush(Array *arr, void *elem);
void ArrayExtend(Array *arr, Array *other);

void *ArrayGet(Array *arr, size_t i);
void ArraySet(Array *arr, size_t i, void *elem);

Array ArraySlice(Array *arr, size_t start, size_t end);

void ArrayMap(Array *arr, void (*fn)(void *elem));
Array *ArrayFilter(Array *arr, bool (*pred)(const void *elem));
void ArrayReduce(Array *arr, void *acc, void (*fn)(void *acc, const void *elem));
void ArraySort(Array *arr, int (*cmp)(const void *, const void *));
void *ArrayFind(Array *arr, bool (*pred)(const void *elem));

double ArraySum(Array *arr);
double ArrayMin(Array *arr);
double ArrayMax(Array *arr);
double ArrayMean(Array *arr);

#endif