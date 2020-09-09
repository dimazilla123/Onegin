#include <stdio.h>
#include "algorithm.h"
#include "vector.h"

bool compare_int(const void* a, const void* b)
{
    return *(int*)a < *(int*)b;
}

bool check_order(const int a[], size_t s)
{
    for (int i = 0; i < s - 1; ++i)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

int main(int argc, char const *argv[])
{
    int a[] = {5, 3, 4, 3, 2, 1};
    sort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), &compare_int);
    if (!check_order(a, sizeof(a) / sizeof(a[0])))
        printf("Wrong order!\n");

    return 0;
}