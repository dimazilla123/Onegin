#include "vector.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>

bool create_vector(Vector* v, size_t len, size_t el_sz)
{
    assert(v != NULL);
    v->len = len;
    v->real_len = (len > 0 ? len : 1);
    v->el_sz = el_sz;
    if (!(v->a = calloc(v->real_len, el_sz)))
        return false;
    return true;
}

bool push_back(Vector* v, void* elem)
{
    void *buffer = NULL;

    assert(v != NULL);
    assert(elem != NULL);
    if (v->len == v->real_len)
    {
        buffer = calloc(v->real_len * 2, v->el_sz);
        if (!buffer)
            return false;
        memcpy(buffer, v->a, v->real_len * v->el_sz);
        free(v->a);
        v->a = buffer;
        v->real_len *= 2;
    }
    memcpy((void*)((char*)(v->a) + (v->len) * v->el_sz), elem, v->el_sz);
    ++v->len;
    return true;
}

void* get_element(Vector v, size_t pos)
{
    assert(pos < v.len);
    return (void*)((char*)(v.a) + v.el_sz * pos);
}

void clean_vector(Vector v)
{
    if (v.a) free(v.a);
}