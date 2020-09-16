#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "algorithm.h"
#include "vector.h"
#include "string_utils.h"

const char* USEAGELINE = "Usage: %s [-h] [-i input] [-o output] [-r reversed_output]\n"
                         "-h prints this help\n"
                         "-i specifices input\n"
                         "-o specifices output\n" 
                         "-r specifices output for reversed sort\n" 
                         "If input is not given, uses stdin\n"
                         "If output is not given, uses, stdout\n";

bool cmpstr(const void *a, const void *b);
bool rcmpstr(const void *a, const void *b);
char *readcontent(FILE *in, size_t *textsz_p);
char **getlines(FILE *in, size_t *lines_cnt_p, char **text_p);

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
    char *text = NULL;
    char **lines = NULL;
    size_t lines_cnt = 0;

    if ((lines = getlines(in, &lines_cnt, &text)) == NULL)
    {
        printf("Cannot split file contents in lines\n");
        return 0;
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

bool cmpstr(const void *a, const void *b)
{
    return strless(*(const unsigned char**)a, *(const unsigned char**)b);
}

bool rcmpstr(const void *a, const void *b)
{
    return strless_reversed(*(const unsigned char**)a, *(const unsigned char**)b);
}

char *readcontent(FILE *in, size_t *textsz_p)
{
    if (in == stdin)
    {
        Vector v;
        create_vector(&v, 1, sizeof(char));
        int c = EOF;
        while ((c = getc(in)) != EOF)
            if (!push_back(&v, &c))
            {
                printf("Cannot pull symbol from stdin!\n");
                return NULL;
            }
        *textsz_p = v.len;
        return v.a;
    }
    fseek(in, 0L, SEEK_END);
    *textsz_p = ftell(in) + 1;
    rewind(in);
    char *text = calloc(*textsz_p, sizeof(text[0]));
    if (!text)
    {
        printf("Cannot allocate memory for text from file!\n");
        return NULL;
    }
    fread(text + 1, *textsz_p - 1, sizeof(char), in);
    return text;
}

char **getlines(FILE *in, size_t *lines_cnt_p, char **text_p)
{
    size_t textsz = 0;
    char *text = readcontent(in, &textsz);
    if (!text)
        return NULL;
    size_t lines_cnt = 0;
    for (int i = 1; i < textsz; ++i)
        if (text[i] == '\n')
            ++lines_cnt;
    char **lines = calloc(lines_cnt, sizeof(char*));
    if (!lines)
    {
        printf("Cannot allocate memory for pointers to lines!\n");
        return NULL;
    }
    size_t len = 0;
    int j = 0;
    for (int i = 1; i < textsz && j < lines_cnt; ++i)
    {
        if (text[i] == '\n')
        {
            lines[j++] = text + i - len;
            text[i] = '\0';
            len = 0;
        } else ++len;
    }
    *lines_cnt_p = lines_cnt;
    *text_p = text;
    return lines;
}