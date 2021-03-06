/*!
 * @file Header of some utilites for processing strings
 */
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include "bool.h"


/*!
 * @fn bool strless(const unsigned char* a, const unsigned char *b)
 * @brief Compares strings lexicographicly
 * Return true if a is lexicograficly less than b in read encoding, ignoring
 * punctuation signs
 * @param a first string, not NULL
 * @param b second string, not NULL
 *
 * @return true if a < b in lexicographical terms
 */
bool strless(const unsigned char* a, const unsigned char *b);

/*!
 * @fn bool strless_reversed(const unsigned char* a, const unsigned char *b)
 * @brief As strless, but treates string backwards
 * As strless, but treates string backwards
 * @param a first string, not NULL
 * @param b second string, not NULL
 *
 * @return true if a < b in lexicographical terms
 */

bool strless_reversed(const unsigned char* a, const unsigned char *b);
/*!
 * @fn char* readstring(FILE *in)
 * @brief Read string from file and return pointer to dynamic array
 * @param in input file
 * @return NULL file has ended, pointer no read string otherwise
 */
char* readstring(FILE *in);
wchar_t get_utf8_rev(const unsigned char* a);

#endif