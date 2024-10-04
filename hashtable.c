#include "hashtable.h"
// #include "set.h"   // Assuming this is the header file for your set ADT
#include <stdlib.h>
#include <string.h>

// Hash function prototype

hashtable_t *hashtable_new(const int num_slots) {
    if (num_slots < 1) {
        return NULL;
    }

    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->table = malloc(sizeof(set_t *) * num_slots);
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }

    ht->num_slots = num_slots;
    for (int i = 0; i < num_slots; i++) {
        ht->table[i] = set_new();
        if (ht->table[i] == NULL) {
            // Clean up in case of failure
            for (int j = 0; j < i; j++) {
                set_delete(ht->table[j], NULL);
            }
            free(ht->table);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    unsigned long hash = hash_string(key) % ht->num_slots;
    return set_insert(ht->table[hash], key, item);
}

void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    unsigned long hash = hash_string(key) % ht->num_slots;
    return set_find(ht->table[hash], key);
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL || fp == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_t *set = ht->table[i];
        // Implement set_print that handles the printing of each set
        set_print(set, fp, itemprint);
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->table[i], arg, itemfunc);
    }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_delete(ht->table[i], itemdelete);
    }
    free(ht->table);
    free(ht);
}

unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

bool hashtable_remove(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return false;
    }
    unsigned long hash = hash_string(key) % ht->num_slots;
    return set_remove(ht->table[hash], key);
}
