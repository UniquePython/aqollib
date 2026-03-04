#include "dtype/dtype.h"

#include <stdlib.h>

size_t GetTypeSize(DType dtype)
{
    size_t type_size;
    switch (dtype)
    {
    case INT:
        type_size = sizeof(int);
        break;
    case LONG:
        type_size = sizeof(long);
        break;
    case LONG_LONG:
        type_size = sizeof(long long);
        break;
    case SHORT:
        type_size = sizeof(short);
        break;
    case UNSIGNED_INT:
        type_size = sizeof(unsigned int);
        break;
    case UNSIGNED_CHAR:
        type_size = sizeof(unsigned char);
        break;
    case SIZE_T:
        type_size = sizeof(size_t);
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