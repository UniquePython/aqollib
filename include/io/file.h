#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

FILE *SafeFOpen(const char *path, const char *mode, bool fatal);
void SafeFClose(FILE **fp);

off_t FileSize(const char *path);
char *FileReadAll(const char *path, size_t *out_size);
bool FileWriteAll(const char *path, const void *data, size_t size);
bool FileAppend(const char *path, const void *data, size_t size);

#endif