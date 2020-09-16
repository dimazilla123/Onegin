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

void test(const unsigned char **ordered_material, size_t n,
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
        (unsigned char*)"И где теперь ее сестра?",
        (unsigned char*)"Не только грусть... душа моя,"
    };
    test((const unsigned char**)exper, sizeof(exper) / sizeof(exper[0]), &strless_reversed);
    unsigned char *ordered_material[] =
    {
        (unsigned char*)"",
        (unsigned char*)",ab.",
        (unsigned char*)",abacaba",
        (unsigned char*)"/abacaba.",
        (unsigned char*)".abacaba,",
        (unsigned char*)",abacaba.",
        (unsigned char*)"a/b/a c   aba",
        (unsigned char*)".a.b,a-c/a\\b,a",
        (unsigned char*)",,,,    abaca////ba",
        (unsigned char*)"aba./././.ca////////ba",
        (unsigned char*)"abcde",
        (unsigned char*)"bcdeff",
        (unsigned char*)"bcf",
        (unsigned char*)"А",
        (unsigned char*)"Б",
        (unsigned char*)"В",
        (unsigned char*)"Г",
        (unsigned char*)"Д",
        (unsigned char*)"Е",
        (unsigned char*)"Ж",
        (unsigned char*)"З",
        (unsigned char*)"И",
        (unsigned char*)"Й",
        (unsigned char*)"К",
        (unsigned char*)"Л",
        (unsigned char*)"М",
        (unsigned char*)"Н",
        (unsigned char*)"О",
        (unsigned char*)"П",
        (unsigned char*)"Р",
        (unsigned char*)"С",
        (unsigned char*)"Т",
        (unsigned char*)"У",
        (unsigned char*)"Ф",
        (unsigned char*)"Х",
        (unsigned char*)"Ц",
        (unsigned char*)"Ч",
        (unsigned char*)"Ш",
        (unsigned char*)"Щ",
        (unsigned char*)"Ъ",
        (unsigned char*)"Ы",
        (unsigned char*)"Ь",
        (unsigned char*)"Э",
        (unsigned char*)"Ю",
        (unsigned char*)"Я",
        (unsigned char*)"а",
        (unsigned char*)"б",
        (unsigned char*)"в",
        (unsigned char*)"г",
        (unsigned char*)"д",
        (unsigned char*)"е",
        (unsigned char*)"ж",
        (unsigned char*)"з",
        (unsigned char*)"и",
        (unsigned char*)"й",
        (unsigned char*)"к",
        (unsigned char*)"л",
        (unsigned char*)"м",
        (unsigned char*)"н",
        (unsigned char*)"о",
        (unsigned char*)"п",
        (unsigned char*)"привет",
        (unsigned char*)"р",
        (unsigned char*)"с",
        (unsigned char*)"т",
        (unsigned char*)"тивирпd",
        (unsigned char*)"у",
        (unsigned char*)"ф",
        (unsigned char*)"х",
        (unsigned char*)"ц",
        (unsigned char*)"ч",
        (unsigned char*)"ш",
        (unsigned char*)"щ",
        (unsigned char*)"ъ",
        (unsigned char*)"ы",
        (unsigned char*)"ь",
        (unsigned char*)"э",
        (unsigned char*)"ю",
        (unsigned char*)"я",
    };
    test((const unsigned char **)ordered_material, sizeof(ordered_material) / sizeof(ordered_material[0]), &strless);

    // Костыль, чтобы избежать ошибки сегментации при попытки изменить литерал
    // (спасибо, read-only .text)
    unsigned char *reversed_material[sizeof(ordered_material) / sizeof(ordered_material[0])] = {};
    for (int i = 0; i < sizeof(ordered_material)/ sizeof(ordered_material[0]); ++i)
    {
        reversed_material[i] = calloc(strlen((const char*)(ordered_material[i])) + 1, 1);
        strcpy((char*)(reversed_material[i]), (const char*)(ordered_material[i]));
        printf("%s\n", reversed_material[i]);
        for (int j = 0; j < strlen((const char*)(reversed_material[i])); ++j)
            printf("%2x ", reversed_material[i][j]);
        putchar('\n');
        reverse((char*)(reversed_material[i]));
        printf("%s\n", reversed_material[i]);
        for (int j = 0; j < strlen((const char*)(reversed_material[i])); ++j)
            printf("%2x ", reversed_material[i][j]);
        putchar('\n');
    }
    test((const unsigned char**)(reversed_material), sizeof(ordered_material) / sizeof(ordered_material[0]), &strless_reversed);

    for (int i = 0; i < sizeof(reversed_material) / sizeof(reversed_material[0]); ++i)
        free(reversed_material[i]);

    return 0;
}