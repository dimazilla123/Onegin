#include <stdlib.h>
#include "vector.h"
#include "string_utils.h"

bool strless(const unsigned char* a, const unsigned char *b)
{
    size_t i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
        ++i;
    return a[i] < b[i];
}

char* readstring(FILE *in)
{
    Vector v;
    create_vector(&v, 0, sizeof(char));
    char c = EOF;
    while ((c = getc(in)) != '\n' && c != EOF)
    {
        if (!push_back(&v, &c))
        {
            fprintf(stderr, "Cannot push_back in readstring!\n");
            exit(-1);
        }
    }
    if (c == EOF && v.len == 0)
    {
        clean_vector(v);
        return NULL;
    }
    return v.a;
}