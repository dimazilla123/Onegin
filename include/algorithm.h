#ifndef ALGORITHM_H
#define ALGORITHM_H

/*!
 * @file Header for several algorithms
 */

#include <stddef.h>
#include "bool.h"

/*!
 * @fn void swap(void *a, void *b, size_t sz)
 * @brief Swaps two objects with equal size\n
 * Swaps two object with given equal size by bytes
 * @param a first pointer to object
 * @param b second pointer to object
 * @param sz size of each object
 */

void swap(void *a, void *b, size_t sz);

/*!
 * @fn void* partition(void *data, size_t c, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
 * @brief Helper function to sort\n
 * Moves items inside array in a from of 3 segments\n
 * 1) Elements that are less than element at position c in inital array (it will be called pivot element)\n
 * 2) Elements that are equal to pivot element\n
 * 3) Elements that are greater that pivot element\n
 * @param data pointer to array
 * @param c positon of pivot element
 * @param n count of elements in array
 * @param s size of one element
 * @param comp pointer to comporator (returns true if a < b)
 * @return pointer to the begining of third segment
 */

void* partition(void *data, size_t c, size_t n, size_t s, bool (*comp)(const void *a, const void *b));

/*!
 * @fn void sort(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
 * @brief Quick sort algorithm realisation\n
 * Sorts element with comparator
 * @param data pointer to array
 * @param n count of elements in array
 * @param s size of one element
 * @param comp pointer to comporator (returns true if a < b)
 */

void sort(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b));

/*!
 * @fn void sort_quad(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b))
 * @brief Quadratic complexity sorting algorithm\n
 * Used for debugging purposes
 * @param data pointer to array
 * @param n count of elements in array
 * @param s size of one element
 * @param comp pointer to comporator (returns true if a < b)
 */

void sort_quad(void *data, size_t n, size_t s, bool (*comp)(const void *a, const void *b));

#endif