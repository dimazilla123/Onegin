#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "algorithm.h"
#include "vector.h"

bool compare_int(const void* a, const void* b)
{
    return *(const int*)a < *(const int*)b;
}

bool compare_long(const void* a, const void* b)
{
    return *(const long*)a < *(const long*)b;
}

long lrand(long nseed)
{
    static long seed = 1;
    if (nseed != 0)
        seed = nseed;
    seed = 1234 * seed % (long)(1e9 + 7);
    return seed;
}

bool check_order(const int a[], size_t s)
{
    for (int i = 0; i < s - 1; ++i)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

bool test_random_sort(int array_length)
{
    int *ia_fast = calloc(array_length, sizeof(ia_fast[0]));
    int *ia_slow = calloc(array_length, sizeof(ia_slow[0]));

    long *la_fast = calloc(array_length, sizeof(la_fast[0]));
    long *la_slow = calloc(array_length, sizeof(la_slow[0]));

    for (int l = 1; l <= array_length; ++l)
    {
        for (int i = 0; i < l; ++i)
            la_fast[i] = la_slow[i] = ia_fast[i] = ia_slow[i] = lrand(0);
        sort(la_fast, l, sizeof(la_fast[0]), &compare_long);
        sort_quad(la_slow, l, sizeof(la_fast[0]), &compare_long);
        sort(ia_fast, l, sizeof(ia_fast[0]), &compare_int);
        sort_quad(ia_slow, l, sizeof(ia_fast[0]), &compare_int);
        for (int i = 0; i < l; ++i)
        {
            if (la_fast[i] != la_slow[i])
            {
                printf("Elements %d are not equal in long!\n", i);
                return false;
            }
            if (ia_fast[i] != ia_slow[i])
            {
                printf("Elements %d are not equal in int!\n", i);
                return false;
            }
        }
    }
    free(ia_fast);
    free(ia_slow);
    free(la_fast);
    free(la_slow);

    return true;
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s seed array_length\n", argv[0]);
        return 0;
    }

    lrand(atol(argv[1]));
    int array_length = atoi(argv[2]);

    if (!test_random_sort(array_length)) return 0;

    int a[] = {5, 3, 4, 3, 2, 1};

    sort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), &compare_int);
    if (!check_order(a, sizeof(a) / sizeof(a[0])))
        printf("Wrong order!\n");

    return 0;
}