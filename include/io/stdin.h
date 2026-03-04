#ifndef STDIN_H
#define STDIN_H

#include <stdio.h>

char *ReadLine(FILE *stream);
char *ReadLinePrompt(const char *prompt);

#endif