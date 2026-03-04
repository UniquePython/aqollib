#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

Arena *ArenaCreate(size_t capacity);
void ArenaDestroy(Arena **arena);

void *ArenaAlloc(Arena *arena, size_t size);
void ArenaReset(Arena *arena);

size_t ArenaSave(Arena *arena);
void ArenaRestore(Arena *arena, size_t checkpoint);

#endif