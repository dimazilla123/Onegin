#ifndef VECTOR_H
#define VECTOR_H
/*!
 * @file Header of c++ vector alternative
 */


#include <stddef.h>
#include "bool.h"

/*!
 * @struct Vector
 * @brief Dynamic array with easy to use push_back()
 *  
 */

struct Vector
{
    /*!
     * @brief Count of elements
     */
    size_t len; /*! Count of elements */
    /*!
     * @brief Count of allocated elements
     */
    size_t real_len; /*! Count of allocated elements */
    /*!
     * @brief Size of one element
     */
    size_t el_sz; /*! Size of one element */
    /*!
     * @brief Pointer to dedicated memory
     */
    void *a; /*! Pointer to dedicated memory. NULL if no memory allocated */
} typedef Vector;

/*!
 * @fn bool create_vector(Vector *v, size_t len, size_t el_sz)
 * @brief Creates new vector
 * Creates new vector with length of len of elements with size el_sz
 * Returns true if vector created or false if allocation failed
 * @param v pointer to vector struct to write results
 * @param len minimal length of vector
 * @param el_sz size of one element
 *
 * @return true if allocation succseed, false otherwise
 */

bool create_vector(Vector* v, size_t len, size_t el_sz);

/*!
 * @fn bool push_back(Vector* v, void* elem)
 * @brief Appends element to vector from behind
 *
 *
 * @param v pointer to vector struct to write results
 * @param elem pointer to the element to be pushed
 *
 * @return true if adding element succseed, false otherwise
 */

bool push_back(Vector* v, void* elem);

/*!
 * @fn void* get_element(Vector v, size_t pos)
 * @brief Returns pointer to pos-element
 *
 *
 * @param v pointer to vector struct to write results
 * @param pos index of element
 *
 * @return pointer to pos-element
 */

void* get_element(Vector v, size_t pos);

/*!
 * @fn void clean_vector(Vector v)
 * @brief Destroys vector
 *
 * Removes allocated array inside vector. Leaves initial value as a garbage
 *
 * @param v vector to clen
 *
 */

void clean_vector(Vector v);

#endif