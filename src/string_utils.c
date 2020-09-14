#include <stdlib.h>
#include "vector.h"
#include "string.h"
#include "string_utils.h"
/*!
 * @fn bool isin(char c, const char s[])
 * @brief check if c in s
 * @param c character, ocurtion which is needed to check
 * @param s string, where character c is searched
 * @return true if c is found, false otherwise
 */
bool isin(char c, const char s[])
{
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return true;
    return false;
}

// List of characters to ignore
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
        if (a[i] != '\0' && a[i] == b[j])
            ++i, ++j;
        else break;
    }
    while (isin(a[i], IGN))
        ++i;
    while (isin(b[j], IGN))
        ++j;
    return a[i] < b[j];
}

bool check_mask(size_t x, size_t ones, size_t zeros)
{
    return (x & ones) == ones && ((~x) & zeros) == zeros;
}

// God, have mercy at this cursed UTF-8 land
/*!
 * @fn wchar_t get_utf8_rev(const unsigned char* a)
 * @brief returns 2 byte UTF-8 character or normal one backwards
 */
wchar_t get_utf8_rev(const unsigned char* a)
{
    const size_t ones =  0b1100000010000000;
    const size_t zeros = 0b0010000001000000;
    wchar_t c = (wchar_t)a[-1] * 256 + a[0];
    if (check_mask(c, ones, zeros))
        return c;
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