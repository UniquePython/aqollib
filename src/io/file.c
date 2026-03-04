#include "io/file.h"
#include "errors/error.h"
#include "memory/safe.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

FILE *SafeFOpen(const char *path, const char *mode, bool fatal)
{
    FILE *fp = fopen(path, mode);

    if (!fp)
    {
        if (fatal)
        {
            fprintf(stderr, "[ERROR] SafeFOpen failed: could not open '%s'\n", path);
            exit(EXIT_FAILURE);
        }
        else
            fprintf(stderr, "[WARNING] SafeFOpen failed: could not open '%s'\n", path);
    }

    return fp;
}

void SafeFClose(FILE **fp)
{
    if (fp && *fp)
    {
        fclose(*fp);
        *fp = NULL;
    }
}

off_t FileSize(const char *path)
{
    struct stat sb;

    if (stat(path, &sb) != 0)
        return -1;

    return sb.st_size;
}

char *FileReadAll(const char *path, size_t *out_size)
{
    off_t size = FileSize(path);
    if (size < 0)
    {
        fprintf(stderr, "[ERROR] FileReadAll failed: could not stat '%s'\n", path);
        return NULL;
    }

    FILE *fp = SafeFOpen(path, "rb", false);
    if (!fp)
        return NULL;

    char *buf = MALLOC_CHAR((size_t)size + 1);
    if (!buf)
    {
        SafeFClose(&fp);
        return NULL;
    }

    size_t nread = fread(buf, 1, (size_t)size, fp);
    SafeFClose(&fp);

    if (nread != (size_t)size)
    {
        fprintf(stderr, "[ERROR] FileReadAll failed: partial read on '%s'\n", path);
        free(buf);
        return NULL;
    }

    buf[size] = '\0';

    if (out_size)
        *out_size = (size_t)size;

    return buf;
}

bool FileWriteAll(const char *path, const void *data, size_t size)
{
    FILE *fp = SafeFOpen(path, "wb", false);
    if (!fp)
        return false;

    size_t nwritten = fwrite(data, 1, size, fp);
    SafeFClose(&fp);

    if (nwritten != size)
    {
        fprintf(stderr, "[ERROR] FileWriteAll failed: partial write on '%s'\n", path);
        return false;
    }

    return true;
}

bool FileAppend(const char *path, const void *data, size_t size)
{
    FILE *fp = SafeFOpen(path, "ab", false);
    if (!fp)
        return false;

    size_t nwritten = fwrite(data, 1, size, fp);
    SafeFClose(&fp);

    if (nwritten != size)
    {
        fprintf(stderr, "[ERROR] FileAppend failed: partial write on '%s'\n", path);
        return false;
    }

    return true;
}