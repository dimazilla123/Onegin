#include "vector.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    Vector v;
    create_vector(&v, n, sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", (int*)get_element(v, i));
    for (int i = 0; i < n; ++i)
        printf("%d\n", *(int*)get_element(v, i));
    return 0;
}