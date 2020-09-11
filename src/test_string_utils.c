#include "vector.h"
#include "string_utils.h"

bool check_order(const unsigned char* a[], size_t s)
{
    for (int i = 0; i < s - 1; ++i)
        if (strless(a[i + 1], a[i]))
            return false;
    return true;
}

int main(int argc, char const *argv[])
{
    const unsigned char* ordered_material[] =
    {
        "",
        ",ab.",
        "abcde",
        "bcdeff",
        "bcf",
        "привет",
        "тивирп"
    };
    const unsigned char* equal_material[] =
    {
        ",abacaba",
        "/abacaba.",
        ".abacaba,",
        ",abacaba.",
        "a/b/a c   aba",
        ".a.b,a-c/a\\b,a",
        ",,,,    abaca////ba",
        "aba./././.ca////////ba",
    };
    for (int r = 0; r < sizeof(ordered_material) / sizeof(ordered_material[0]); ++r)
    {
        for (int l = 0; l < r; ++l)
        {
            if (!(strless(ordered_material[l], ordered_material[r])
              && !strless(ordered_material[r], ordered_material[l])))
            {
                printf("Wrong order: %d < %d\n", l, r);
                return 0;
            }
        }
    }
    for (int i = 0; i < sizeof(equal_material) / sizeof(equal_material[0]); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (strless(equal_material[i], equal_material[j])
             || strless(equal_material[j], equal_material[i]))
            {
                printf("Equal seems different: %d = %d\n", i, j);
                return 0;
            }
        }
    }
    return 0;
}