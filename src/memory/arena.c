#include "memory/arena.h"
#include "errors/error.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct Arena
{
    unsigned char *buf;
    size_t capacity;
    size_t offset;
};

static size_t AlignUp(size_t offset, size_t align)
{
    return (offset + align - 1) & ~(align - 1);
}

Arena *ArenaCreate(size_t capacity)
{
    Arena *arena = malloc(sizeof(Arena));
    HANDLE_NULL_PTR(arena, "ArenaCreate failed: could not allocate arena struct");

    arena->buf = malloc(capacity);
    HANDLE_NULL_PTR(arena->buf, "ArenaCreate failed: could not allocate arena buffer");

    arena->capacity = capacity;
    arena->offset = 0;

    return arena;
}

void ArenaDestroy(Arena **arena)
{
    if (arena && *arena)
    {
        free((*arena)->buf);
        free(*arena);
        *arena = NULL;
    }
}

void *ArenaAlloc(Arena *arena, size_t size)
{
    size_t aligned = AlignUp(arena->offset, _Alignof(max_align_t));

    if (aligned + size > arena->capacity)
    {
        fprintf(stderr, "[ERROR] ArenaAlloc failed: arena out of capacity\n");
        return NULL;
    }

    void *ptr = arena->buf + aligned;
    arena->offset = aligned + size;

    return ptr;
}

void ArenaReset(Arena *arena)
{
    arena->offset = 0;
}

size_t ArenaSave(Arena *arena)
{
    return arena->offset;
}

void ArenaRestore(Arena *arena, size_t checkpoint)
{
    arena->offset = checkpoint;
}