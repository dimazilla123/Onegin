#include <stdlib.h>
#include "string_utils.h"

bool strless(const char* a, const char *b)
{
    size_t i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
        ++i;
    return a[i] < b[i];
}

char* readstring(FILE *in)
{
    static const size_t MAXSIZE = 41;
    size_t current = MAXSIZE;
    char *s = calloc(MAXSIZE, sizeof(char));
    if (!s)
    {
        perror("Cannot allocate space for input line!");
        return NULL;
    }
    char *buffer = NULL;
    int c = 0;
    int i = 0, j = 0;
    while ((c = getc(in)) != EOF && c != '\n')
    {
        s[i] = c;
        ++i;
        if (i == current)
        {
            buffer = calloc(current * 2, sizeof(char));
            if (!buffer)
            {
                perror("Cannot expand space for input line!");
                return NULL;
            }
            for (j = 0; j < current; ++j)
                buffer[j] = s[j];
            current *= 2;
            free(s);
            s = buffer;
        }
    }
    if (current == MAXSIZE && s[0] == 0) {
        free(s);
        return NULL;
    }
    return s;
}