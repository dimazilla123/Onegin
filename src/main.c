#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "algorithm.h"
#include "string_utils.h"

const char* USEAGELINE = "Usage: %s [-h] [-i input] [-o output] [-r reversed_output]\n"
                         "-h prints this help\n"
                         "-i specifices input\n"
                         "-o specifices output\n" 
                         "-r specifices output for reversed sort\n" 
                         "If input is not given, uses stdin\n"
                         "If output is not given, uses, stdout\n";

bool cmpstr(const void *a, const void *b)
{
    return strless(*(const unsigned char**)a, *(const unsigned char**)b);
}

bool rcmpstr(const void *a, const void *b)
{
    return strless_reversed(*(const unsigned char**)a, *(const unsigned char**)b);
}

int main(int argc, char *const argv[])
{
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *rout = stdout;
    int opt = 0;

    while ((opt = getopt(argc, argv, "hi:o:r:")) != -1)
    {
        switch (opt)
        {
            case 'h':
            {
                printf(USEAGELINE, argv[0]);
                return 0;
                break;
            }
            case 'i':
            {
                in = fopen(optarg, "r");
                if (in == NULL)
                {
                    fprintf(stderr, "Cannot open input file!\n");
                    return 0;
                }
                break;
            }
            case 'o':
            {
                out = fopen(optarg, "w");
                if (out == NULL)
                {
                    fprintf(stderr, "Cannot open out file!\n");
                    return 0;
                }
                break;
            }
            case 'r':
            {
                rout = fopen(optarg, "w");
                if (rout == NULL)
                {
                    fprintf(stderr, "Cannot open output for reversed file!\n");
                    return 0;
                }
                break;
            }
        }
    }

    const size_t MAXSZ = 1024 * 1024;
    char *text = calloc(MAXSZ, sizeof(text[0]));
    if (!text)
    {
        printf("Cannot allocate memory for file contents!\n");
        return 0;
    }
    size_t textsz = fread(text, sizeof(text[0]), MAXSZ, in);
    size_t lines_cnt = 0;
    for (int i = 0; i < textsz; ++i)
        if (text[i] == '\n')
            ++lines_cnt;
    char **lines = calloc(lines_cnt, sizeof(char*));
    if (!lines)
    {
        printf("Cannot allocate memory for pointers to lines!\n");
        return 0;
    }
    size_t len = 0;
    int j = 0;
    for (int i = 0; i < textsz && j < lines_cnt; ++i)
    {
        if (text[i] == '\n')
        {
            lines[j++] = text + i - len;
            text[i] = '\0';
            len = 0;
        } else ++len;
    }

    sort(lines, lines_cnt, sizeof(lines[0]), &cmpstr);
    for (int i = 0; i < lines_cnt; ++i)
        fprintf(out, "%s\n", lines[i]);
    sort(lines, lines_cnt, sizeof(lines[0]), &rcmpstr);
    for (int i = 0; i < lines_cnt; ++i)
        fprintf(rout, "%s\n", lines[i]);

    free(text);
    free(lines);

    fclose(in);
    fclose(out);
    fclose(rout);

    return 0;
}