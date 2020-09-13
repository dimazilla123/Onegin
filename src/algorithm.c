#include "algorithm.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

size_t dist(const void* a, const void *b)
{
    return (const char*)b - (const char*)a;
}

void swap(void *a, void *b, size_t sz)
{
    int i = 0;
    char t;
    for (i = 0; i < sz; ++i) {
        t = *((char*)b + i);
        *((char*)b + i) = *((char*)a + i);
        *((char*)a + i) = t;
    }
}

void* partition(void *data, size_t c, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
{
    char* l = (char*)data;
    char* r = (char*)data + (n - 1) * s;
    void *pivot = calloc(1, s);
    if (!pivot)
    {
        fprintf(stderr, "Cannot allocate memory for pivot element!\n");
        exit(0);
    }
    memcpy(pivot, (const char*)data + c * s, s);
    while (l <= r)
    {
        while ((*comp)((void*)l, pivot))
            l += s;
        while ((*comp)(pivot, (void*)r))
            r -= s;
        if (l >= r)
        {
            break;
        }
        swap(l, r, s);
        l += s;
        r -= s;
    }
    free(pivot);
    return r + s;
}


void sort(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
{
    //static char* START = NULL;
    //if (!START)
    //    START = data;
    //fprintf(stderr, "%d %d\n", dist(START, data) / s, dist(START, data) / s + n);
    if (n <= 1)
        return;
    if (n == 2)
    {
        if (!(*comp)(data, (char*)data + s))
            swap(data, (char*)data + s, s);
        return;
    }
    void *m = partition(data, n / 2, n, s, comp);
    sort(data, dist(data, m) / s, s, comp);
    sort(m, n - dist(data, m) / s, s, comp);
}

void sort_quad(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
{
    int i = 0;
    int j = 0;
    void *ip, *jp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            ip = (void*)((const char*)data + i * s);
            jp = (void*)((const char*)data + j * s);
            if (!(*comp)(jp, ip))
                swap(ip, jp, s);
        }
    }
}