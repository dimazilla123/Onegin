#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stddef.h>
#include "bool.h"

void swap(void *a, void *b, size_t sz);

void sort(void *data, size_t n, size_t s, bool (*comp)(void *a, void *b));

#endif