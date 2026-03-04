#include "array/array.h"
#include "errors/error.h"
#include "dtype/dtype.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define GROWTH_FACTOR 2
#define MIN_CAPACITY 8

static void *ElemAt(Array *arr, size_t i)
{
    return (unsigned char *)arr->data + i * GetTypeSize(arr->dtype);
}

static double ElemToDouble(const void *elem, DType dtype)
{
    switch (dtype)
    {
    case INT:
        return (double)(*(int *)elem);
    case LONG:
        return (double)(*(long *)elem);
    case LONG_LONG:
        return (double)(*(long long *)elem);
    case SHORT:
        return (double)(*(short *)elem);
    case UNSIGNED_INT:
        return (double)(*(unsigned int *)elem);
    case UNSIGNED_CHAR:
        return (double)(*(unsigned char *)elem);
    case SIZE_T:
        return (double)(*(size_t *)elem);
    case DOUBLE:
        return *(double *)elem;
    case FLOAT:
        return (double)(*(float *)elem);
    case CHAR:
        return (double)(*(char *)elem);
    default:
        return 0.0;
    }
}

static void GrowIfNeeded(Array *arr)
{
    if (arr->length < arr->capacity)
        return;

    size_t new_capacity = arr->capacity * GROWTH_FACTOR;
    void *new_data = realloc(arr->data, new_capacity * GetTypeSize(arr->dtype));
    HANDLE_NULL_PTR(new_data, "Array growth failed: out of memory");

    arr->data = new_data;
    arr->capacity = new_capacity;
}

Array *ArrayCreate(DType dtype, size_t capacity)
{
    if (capacity < MIN_CAPACITY)
        capacity = MIN_CAPACITY;

    Array *arr = malloc(sizeof(Array));
    HANDLE_NULL_PTR(arr, "ArrayCreate failed: could not allocate array struct");

    arr->data = malloc(capacity * GetTypeSize(dtype));
    HANDLE_NULL_PTR(arr->data, "ArrayCreate failed: could not allocate array buffer");

    arr->dtype = dtype;
    arr->length = 0;
    arr->capacity = capacity;
    arr->owned = true;

    return arr;
}

Array *ArrayFrom(DType dtype, void *data, size_t length)
{
    Array *arr = ArrayCreate(dtype, length);

    memcpy(arr->data, data, length * GetTypeSize(dtype));
    arr->length = length;

    return arr;
}

void ArrayDestroy(Array **arr)
{
    if (arr && *arr)
    {
        if ((*arr)->owned)
            free((*arr)->data);
        free(*arr);
        *arr = NULL;
    }
}

void ArrayPush(Array *arr, void *elem)
{
    GrowIfNeeded(arr);
    memcpy(ElemAt(arr, arr->length), elem, GetTypeSize(arr->dtype));
    arr->length++;
}

void ArrayExtend(Array *arr, Array *other)
{
    for (size_t i = 0; i < other->length; i++)
        ArrayPush(arr, ElemAt(other, i));
}

void *ArrayGet(Array *arr, size_t i)
{
    if (i >= arr->length)
    {
        fprintf(stderr, "[ERROR] ArrayGet: index %zu out of bounds (length %zu)\n", i, arr->length);
        return NULL;
    }

    return ElemAt(arr, i);
}

void ArraySet(Array *arr, size_t i, void *elem)
{
    if (i >= arr->length)
    {
        fprintf(stderr, "[ERROR] ArraySet: index %zu out of bounds (length %zu)\n", i, arr->length);
        return;
    }

    memcpy(ElemAt(arr, i), elem, GetTypeSize(arr->dtype));
}

Array ArraySlice(Array *arr, size_t start, size_t end)
{
    if (start > end || end > arr->length)
    {
        fprintf(stderr, "[ERROR] ArraySlice: invalid range [%zu, %zu) for length %zu\n",
                start, end, arr->length);
        return (Array){0};
    }

    return (Array){
        .data = ElemAt(arr, start),
        .dtype = arr->dtype,
        .length = end - start,
        .capacity = 0,
        .owned = false};
}

void ArrayMap(Array *arr, void (*fn)(void *elem))
{
    for (size_t i = 0; i < arr->length; i++)
        fn(ElemAt(arr, i));
}

Array *ArrayFilter(Array *arr, bool (*pred)(const void *elem))
{
    Array *out = ArrayCreate(arr->dtype, arr->length);

    for (size_t i = 0; i < arr->length; i++)
    {
        void *elem = ElemAt(arr, i);
        if (pred(elem))
            ArrayPush(out, elem);
    }

    return out;
}

void ArrayReduce(Array *arr, void *acc, void (*fn)(void *acc, const void *elem))
{
    for (size_t i = 0; i < arr->length; i++)
        fn(acc, ElemAt(arr, i));
}

void ArraySort(Array *arr, int (*cmp)(const void *, const void *))
{
    qsort(arr->data, arr->length, GetTypeSize(arr->dtype), cmp);
}

void *ArrayFind(Array *arr, bool (*pred)(const void *elem))
{
    for (size_t i = 0; i < arr->length; i++)
    {
        void *elem = ElemAt(arr, i);
        if (pred(elem))
            return elem;
    }

    return NULL;
}

double ArraySum(Array *arr)
{
    double sum = 0.0;

    for (size_t i = 0; i < arr->length; i++)
        sum += ElemToDouble(ElemAt(arr, i), arr->dtype);

    return sum;
}

double ArrayMin(Array *arr)
{
    if (arr->length == 0)
        return 0.0;

    double min = ElemToDouble(ElemAt(arr, 0), arr->dtype);

    for (size_t i = 1; i < arr->length; i++)
    {
        double val = ElemToDouble(ElemAt(arr, i), arr->dtype);
        if (val < min)
            min = val;
    }

    return min;
}

double ArrayMax(Array *arr)
{
    if (arr->length == 0)
        return 0.0;

    double max = ElemToDouble(ElemAt(arr, 0), arr->dtype);

    for (size_t i = 1; i < arr->length; i++)
    {
        double val = ElemToDouble(ElemAt(arr, i), arr->dtype);
        if (val > max)
            max = val;
    }

    return max;
}

double ArrayMean(Array *arr)
{
    if (arr->length == 0)
        return 0.0;

    return ArraySum(arr) / (double)arr->length;
}