#include <stdlib.h>
#include "vector.h"
#include "string.h"
#include "string_utils.h"

bool isin(char c, const char s[])
{
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return true;
    return false;
}

const char IGN[] = " ,.-\t\\/\"\'!?:;()";

bool strless(const unsigned char* a, const unsigned char *b)
{
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
}

wchar_t get_utf8_rev(const unsigned char* a)
{
    static const unsigned char RUSSIAN[] = u8"абвгдеёжзийклмнопрстуфхцчшщыъьэюя"
                                      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЪЬЭЮЯ";
    wchar_t c = (wchar_t)a[-1] * 256 + a[0];
    for (int i = 0; i < sizeof(RUSSIAN) / sizeof(RUSSIAN[0]) / 2; ++i)
    {
        wchar_t d = (wchar_t)RUSSIAN[2 * i] * 256 + RUSSIAN[2 * i + 1];
        if (c == d)
            return c;
    }
    return a[0];
}

bool strless_reversed(const unsigned char* a, const unsigned char *b)
{
    size_t i = strlen(a);
    size_t j = strlen(b);
    while (i != 0 && j != 0)
    {
        while (i != 0 && isin(a[i - 1], IGN))
            --i;
        while (j != 0 && isin(b[j - 1], IGN))
            --j;
        if (i != 0 && j != 0 && a[i - 1] == b[j - 1])
            --i, --j;
        else break;
    }
    wchar_t last_a = (i == 0 || isin(a[i - 1], IGN) ? '\0' : a[i - 1]);
    if (i > 1)
        last_a = get_utf8_rev(a + i - 1);
    wchar_t last_b = (j == 0 || isin(b[j - 1], IGN) ? '\0' : b[j - 1]);
    if (j > 1)
        last_b = get_utf8_rev(b + j - 1);
    return last_a < last_b;
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