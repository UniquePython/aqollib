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