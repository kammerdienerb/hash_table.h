/*
 * hash_table_test.c
 */

#include <stdio.h>
#include <string.h>

#include "hash_table.h"

uint64_t int_hash(int i) { return i; }
use_hash_table(int, float);

typedef char *str;
uint64_t str_hash(str s) {
    unsigned long hash = 5381;
    int c;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
int str_equ(str a, str b) { return strcmp(a, b) == 0; }
use_hash_table(str, str);

int main(int argc, char **argv) {
    hash_table(int, float) t;
    hash_table(str, str) s_t;

    t   = hash_table_make(int, float, int_hash); 
    s_t = hash_table_make_e(str, str, str_hash, str_equ); 

    for (int i = 0; i < 100; i += 1) {
        hash_table_insert(t, i * i, (float)i);
    }

    int    i;
    float *f_ptr;
    hash_table_traverse(t, i, f_ptr) {
        *f_ptr /= 3;
    }

    float *f_search;
    if ((f_search = hash_table_get_val(t, 49))) {
        printf("found 49: sqrt() is %f\n", *f_search * 3);
    } else {
        printf("did not find 49\n");
    }
    if ((f_search = hash_table_get_val(t, 80))) {
        printf("found 80: sqrt() is %f\n", *f_search * 3);
    } else {
        printf("did not find 80\n");
    }
    
    hash_table_insert(s_t, strdup("epoch"),    strdup("exultant"));
    hash_table_insert(s_t, strdup("scarf"),    strdup("magic"));
    hash_table_insert(s_t, strdup("feeling"),  strdup("general"));
    hash_table_insert(s_t, strdup("fearless"), strdup("tremendous"));
    hash_table_insert(s_t, strdup("helpful"),  strdup("fool"));
    hash_table_insert(s_t, strdup("laugh"),    strdup("tan"));
    hash_table_insert(s_t, strdup("toe"),      strdup("tacky"));
    hash_table_insert(s_t, strdup("flight"),   strdup("eager"));
    hash_table_insert(s_t, strdup("oval"),     strdup("income"));
    hash_table_insert(s_t, strdup("jitter"),   strdup("weigh"));
    hash_table_insert(s_t, strdup("yam"),      strdup("small"));
    hash_table_insert(s_t, strdup("aloof"),    strdup("popsicle"));

    if (hash_table_delete(s_t, "doesn't exist")) {
        printf("how did we delete a key that doesn't exist?\n");
    }

    char *k, **k_ptr,
         *v, **v_ptr;

    k_ptr = hash_table_get_key(s_t, "oval");
    v_ptr = hash_table_get_val(s_t, "oval");

    if (k_ptr) { k = *k_ptr; }
    if (v_ptr) { v = *v_ptr; }

    if (hash_table_delete(s_t, "oval")) {
        printf("deleted 'oval'\n");
        free(k);
        free(v);
    }

    printf("\n");

    int max_len = 0;
    hash_table_traverse(s_t, k, v_ptr) {
        int l = strlen(k);
        if (l > max_len)
            max_len = l;
    }
    hash_table_traverse(s_t, k, v_ptr) {
        printf("%*s %s\n", -max_len, k, *v_ptr);
        free(k);
        free(*v_ptr);
    }

    hash_table_free(s_t);
    hash_table_free(t);
}
