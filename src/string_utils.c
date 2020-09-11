#include <stdlib.h>
#include "vector.h"
#include "string_utils.h"

bool isin(char c, const char s[])
{
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return true;
    return false;
}

bool strless(const unsigned char* a, const unsigned char *b)
{
    static const char IGN[] = " ,.-\t\\/";
    size_t i = 0;
    size_t j = 0;
    while (a[i] != '\0' && b[j] != '\0')
    {
        while (isin(a[i], IGN))
            ++i;
        while (isin(b[j], IGN))
            ++j;
        if (a[i] == b[j])
            ++i, ++j;
        else break;
    }
    while (isin(a[i], IGN))
        ++i;
    while (isin(b[j], IGN))
        ++j;
    return a[i] < b[j];
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