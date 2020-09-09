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
    const unsigned char* material[] =
    {
        "",
        "ab"
        "abcde",
        "bcdeff",
        "bcf",
        "привет"
    };
    if (!check_order(material, sizeof(material) / sizeof(material[0])))
        printf("Wrong order!\n");
    return 0;
}