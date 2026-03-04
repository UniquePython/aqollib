#ifndef DTYPE_H
#define DTYPE_H

typedef enum e_dtype
{
    INT,
    LONG,
    LONG_LONG,
    SHORT,
    UNSIGNED_INT,
    UNSIGNED_CHAR,
    SIZE_T,
    DOUBLE,
    FLOAT,
    CHAR
} DType;

size_t GetTypeSize(DType dtype);

#endif