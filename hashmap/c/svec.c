/* This file is lecture notes from CS 3650, Fall 2018 */
/* Author: Nat Tuck */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "svec.h"

svec*
make_svec()
{
    svec* sv = calloc(1, sizeof(svec));
    // DONE: correctly allocate and initialize data structure
    sv->cap = 2;
    sv->data = calloc(sv->cap, sizeof(char*));
    sv->size = 0;
    return sv;
}

void
free_svec(svec* sv)
{
    // DONE: free all allocated data
    for(long ii = 0; ii < sv->size; ++ii) {
        free(sv->data[ii]);
    }
    free(sv->data);
    free(sv);
}

char*
svec_get(svec* sv, int ii)
{
    assert(ii >= 0 && ii < sv->size);
    return sv->data[ii];
}

void
svec_put(svec* sv, int ii, char* item)
{
    assert(ii >= 0 && ii < sv->size);
    // DONE: insert item into slot ii
    // Consider ownership of string in collection.
    sv->data[ii] = strdup(item);
}

void
svec_push_back(svec* sv, char* item)
{
    int ii = sv->size;

    // DONE: expand vector if backing erray
    // is not big enough
    if (ii == sv->cap) {
        sv->cap = sv->cap * 2;
        sv->data = realloc(sv->data, sv->cap * sizeof(char*));
    }

    sv->size = ii + 1;
    svec_put(sv, ii, item);
}

void
svec_swap(svec* sv, int ii, int jj)
{
    // DONE: Swap the items in slots ii and jj
    char* tmp = svec_get(sv, ii);
    sv->data[ii] = sv->data[jj];
    sv->data[jj] = tmp;
    /* svec_put(sv, ii, svec_get(sv, jj)); */
    /* svec_put(sv, jj, tmp); */
}
