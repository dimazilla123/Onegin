#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "algorithm.h"
#include "string_utils.h"
#include "vector.h"

const char* USEAGELINE = "Usage: %s [-h] [-i input] [-o output]\n"
                         "-h prints this help\n"
                         "-i specifices input\n"
                         "-o specifices output\n" 
                         "If input is not given, uses stdin\n"
                         "If output is not given, uses, stdout\n";

bool cmpstr(void *a, void *b)
{
    return strless(*(const char**)a, *(const char**)b);
}

int main(int argc, char const *argv[])
{
    FILE *in = stdin;
    FILE *out = stdout;
    int opt = 0;

    while ((opt = getopt(argc, argv, "hi:o:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf(USEAGELINE, argv[0]);
                return 0;
                break;
            case 'i':
                in = fopen(optarg, "r");
                if (in == NULL)
                {
                    fprintf(stderr, "Cannot open input file!\n");
                    return 0;
                }
                break;
            case 'o':
                out = fopen(optarg, "w");
                if (out == NULL)
                {
                    fprintf(stderr, "Cannot open out file!\n");
                    return 0;
                }
                break;
        }
    }

    Vector strs;
    create_vector(&strs, 1, sizeof(char*));
    char *inp = NULL;
    while ((inp = readstring(in)) != NULL)
    {
        if (!push_back(&strs, &inp))
        {
            fprintf(stderr, "push_back failed at element № %lu!\n", strs.len);
            return 0;
        }
    }
    sort(strs.a, strs.len, strs.el_sz, &cmpstr);
    for (int i = 0; i < strs.len; ++i)
        fprintf(out, "%s\n", *(char**)get_element(strs, i));

    clean_vector(strs);

    fclose(in);
    fclose(out);

    return 0;
}