#include "algorithm.h"

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

void sort(void *data, size_t n, size_t s, bool (*comp)(void *a, void *b))
{
    int i = 0;
    int j = 0;
    void *ip, *jp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            ip = (void*)((const char*)data + i * s);
            jp = (void*)((const char*)data + j * s);
            if ((*comp)(jp, ip))
                swap(ip, jp, s);
        }
    }
}