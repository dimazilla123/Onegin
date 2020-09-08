#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stddef.h>
#include "bool.h"

void swap(void *a, void *b, size_t sz);

void* partition(void *data, size_t c, size_t n, size_t s, bool (*comp)(const void *a, const void *b));
void sort(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b));
void sort_quad(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b));

#endif