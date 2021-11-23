
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// See "man strlcpy"
#include <bsd/string.h>
#include <string.h>

#include "hashmap.h"


long
hash(char* key)
{
    // I'm using the djb2 hash function that I found online
    // http://www.cse.yorku.ca/~oz/hash.html
    // DONE: Produce an appropriate hash value.
    long hash = 5381;
    int c;

    while (c = *key++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

hashmap*
make_hashmap_presize(int nn)
{
    hashmap* hh = calloc(1, sizeof(hashmap));
    // Double check "man calloc" to see what that function does.
    hh->size = 0;
    hh->cap = nn;
    hh->data = malloc(hh->cap * sizeof(hashmap_pair));
    for (long ii = 0; ii < nn; ++ii) {
        strncpy(hh->data[ii].key, "", 4);
        hh->data[ii].val = 0;
        hh->data[ii].used = 0;
        hh->data[ii].tomb = 0;
    }

    return hh;
}

hashmap*
make_hashmap()
{
    return make_hashmap_presize(4);
}

void
free_hashmap(hashmap* hh)
{
    free(hh->data);
    free(hh);
}

int
hashmap_has(hashmap* hh, char* kk)
{
    return hashmap_get(hh, kk) != -1;
}

int
hashmap_get(hashmap* hh, char* kk)
{
    // key kk.
    // Note: return -1 for key not found.
    long key_hash = hash(kk) & (hh->cap - 1);
    while (hh->data[key_hash].used) {
        if (strcmp(hh->data[key_hash].key, kk) == 0 && !hh->data[key_hash].tomb) {
            return hh->data[key_hash].val;
        }
        key_hash = (key_hash + 1) & (hh->cap - 1);
    }
    return -1;
}

void hashmap_grow(hashmap* hh)
{
    long old_cap = hh->cap;
    hashmap_pair* old_data = hh->data;

    hh->cap = old_cap * 2;
    hh->data = calloc(hh->cap, sizeof(hashmap_pair));
    hh->size = 0;
    for (long ii = 0; ii < old_cap; ++ii) {
        if (old_data[ii].used) {
            hashmap_put(hh, old_data[ii].key, old_data[ii].val);
        }
    }
    free(old_data);
}

void
hashmap_put(hashmap* hh, char* kk, int vv)
{
    // for the key 'kk', replacing any existing value
    // for that key.

    // max load factor of 0.5
    if (2 * hh->size >= hh->cap) {
        hashmap_grow(hh);
    }
    long key_hash = hash(kk) & (hh->cap - 1);
    // loop through until you find an empty cell
    // or a cell with the same key
    while(hh->data[key_hash].used) {
        if (strcmp(hh->data[key_hash].key, kk) == 0) {
            hh->data[key_hash].val = vv;
            hh->data[key_hash].tomb = 0;
            return;
        }
        key_hash = (key_hash + 1) & (hh->cap - 1);
    }

    // put this k,v pair into the current table entry
    hh->size += 1;
    strncpy(hh->data[key_hash].key, kk, 4);
    hh->data[key_hash].val = vv;
    hh->data[key_hash].used = 1;
    hh->data[key_hash].tomb = 0;
}


void
hashmap_del(hashmap* hh, char* kk)
{
    // this key in the map.
    // if the key is not in the map, return
    if (!hashmap_has(hh, kk)) {
        return;
    }

    // otherwise, hash the key
    long key_hash = hash(kk) & (hh->cap - 1);
    while (hh->data[key_hash].used) {
        // if this is the cell to delete
        if (strcmp(hh->data[key_hash].key, kk) == 0) {
            hh->data[key_hash].tomb = 1;
        }
        key_hash = (key_hash + 1) & (hh->cap - 1);
    }

}


hashmap_pair
hashmap_get_pair(hashmap* hh, int ii)
{
    // DONE: Get the {k,v} pair stored in index 'ii'.
    return hh->data[ii];
}

void
hashmap_dump(hashmap* hh)
{
    printf("== hashmap dump ==\n");
    // DONE: Print out all the keys and values currently
    // in the map, in storage order. Useful for debugging.
    for (long ii = 0; ii < hh->cap; ++ii) {
        hashmap_pair pp = hashmap_get_pair(hh, ii);
        /* printf("Entry %ld: key = %s, val = %d, used = %d, tomb = %d\n", */
        /*        ii, hh->data[ii]->key, hh->data[ii]->val, hh->data[ii]->used, hh->data[ii]->tomb); */
        printf("Entry %ld: key = %s, val = %d, used = %d, tomb = %d\n",
            ii, pp.key, pp.val, pp.used, pp.tomb);

    }
}
