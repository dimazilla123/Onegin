#include "vector.h"
#include "string_utils.h"
#include "algorithm.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

bool check_order(const unsigned char* a[], size_t s)
{
    for (int i = 0; i < s - 1; ++i)
        if (strless(a[i + 1], a[i]))
            return false;
    return true;
}

void test(const unsigned char *ordered_material[], size_t n,
    bool (*cmp)(const unsigned char *a, const unsigned char *b))
{
    for (int r = 0; r < n; ++r)
    {
        for (int l = 0; l < r; ++l)
        {
            if ((*cmp)(ordered_material[r], ordered_material[l]))
            {
                printf("Wrong order at %d %d: %s > %s\n", l, r,
                    ordered_material[l], ordered_material[r]);
                exit(0);
                return;
            }
        }
    }
}

void reverse(char s[])
{
    static char *buffer = NULL;
    size_t l = strlen(s);
    buffer = realloc(buffer, l);
    size_t j = l - 1;
    char t = '\0';
    unsigned char b2[2] = "  ";
    for (size_t i = 0; i < l; ++i)
    {
        if (i < l - 1)
        {
            b2[0] = s[i];
            b2[1] = s[i + 1];
            if (get_utf8_rev(b2 + 1) > 256)
            {
                buffer[l - i - 1] = b2[1];
                buffer[l - i - 2] = b2[0];
                ++i;
            }
            else buffer[l - i - 1] = s[i];
        } else buffer[l - i - 1] = s[i];
    }
    for (int i = 0; i < l; ++i)
        s[i] = buffer[i];
    return;
    for (size_t i = 0; i < l / 2; ++i)
    {
        t = s[i];
        s[i] = s[l - i - 1];
        s[l - i - 1] = t;
    }
}

int main(int argc, char const *argv[])
{
    unsigned char *exper[] =
    {
        "И где теперь ее сестра?",
        "Не только грусть... душа моя,"
    };
    test(exper, sizeof(exper) / sizeof(exper[0]), &strless_reversed);
    unsigned char *ordered_material[] =
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
        "А",
        "Б",
        "В",
        "Г",
        "Д",
        "Е",
        "Ж",
        "З",
        "И",
        "Й",
        "К",
        "Л",
        "М",
        "Н",
        "О",
        "П",
        "Р",
        "С",
        "Т",
        "У",
        "Ф",
        "Х",
        "Ц",
        "Ч",
        "Ш",
        "Щ",
        "Ъ",
        "Ы",
        "Ь",
        "Э",
        "Ю",
        "Я",
        "а",
        "б",
        "в",
        "г",
        "д",
        "е",
        "ж",
        "з",
        "и",
        "й",
        "к",
        "л",
        "м",
        "н",
        "о",
        "п",
        "привет",
        "р",
        "с",
        "т",
        "тивирпd",
        "у",
        "ф",
        "х",
        "ц",
        "ч",
        "ш",
        "щ",
        "ъ",
        "ы",
        "ь",
        "э",
        "ю",
        "я",
    };
    test(ordered_material, sizeof(ordered_material) / sizeof(ordered_material[0]), &strless);

    // Костыль, чтобы избежать ошибки сегментации при попытки изменить литерал
    // (спасибо, read-only .text)
    unsigned char *reversed_material[sizeof(ordered_material) / sizeof(ordered_material[0])] = {};
    for (int i = 0; i < sizeof(ordered_material)/ sizeof(ordered_material[0]); ++i)
    {
        reversed_material[i] = calloc(strlen(ordered_material[i]) + 1, 1);
        strcpy(reversed_material[i], ordered_material[i]);
        printf("%s\n", reversed_material[i]);
        for (int j = 0; j < strlen(reversed_material[i]); ++j)
            printf("%2x ", reversed_material[i][j]);
        putchar('\n');
        reverse(reversed_material[i]);
        printf("%s\n", reversed_material[i]);
        for (int j = 0; j < strlen(reversed_material[i]); ++j)
            printf("%2x ", reversed_material[i][j]);
        putchar('\n');
    }
    test(reversed_material, sizeof(ordered_material) / sizeof(ordered_material[0]), &strless_reversed);

    for (int i = 0; i < sizeof(reversed_material) / sizeof(reversed_material[0]); ++i)
        free(reversed_material[i]);

    return 0;
}