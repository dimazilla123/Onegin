#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include "bool.h"

bool strless(const unsigned char* a, const unsigned char *b);
char* readstring(FILE *in);

#endif