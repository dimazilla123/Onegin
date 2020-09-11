#include "vector.h"
#include "string_utils.h"

bool check_order(const unsigned char* a[], size_t s)
{
    for (int i = 0; i < s - 1; ++i)
        if (strless(a[i + 1], a[i]))
            return false;
    return true;
}

void test(const unsigned char *ordered_material[], size_t n)
{
    for (int r = 0; r < n; ++r)
    {
        for (int l = 0; l < r; ++l)
        {
            if (strless(ordered_material[r], ordered_material[l]))
            {
                printf("Wrong order: %d > %d\n", l, r);
                return;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    const unsigned char* ordered_material[] =
    {
        "",
        ",ab.",
        ",abacaba",
        "/abacaba.",
        ".abacaba,",
        ",abacaba.",
        "a/b/a c   aba",
        ".a.b,a-c/a\\b,a",
        ",,,,    abaca////ba",
        "aba./././.ca////////ba",
        "abcde",
        "bcdeff",
        "bcf",
        "привет",
        "тивирп"
    };
    test(ordered_material, sizeof(ordered_material) / sizeof(ordered_material[0]));
    return 0;
}