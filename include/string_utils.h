#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include "bool.h"

bool strless(const char* a, const char *b);
char* readstring(FILE *in);

#endif