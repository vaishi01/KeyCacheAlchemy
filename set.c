#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

// Create a new set
set_t* set_new(void) {
    set_t *set = malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL;
    }
    set->head = NULL;
    set->call_itemdelete = true;  // Default to true, adjust based on your application logic
    return set;
}

// Insert an item into the set
bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    }

    // Check if key already exists
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return false;
        }
    }

    // Create new node
    setnode_t *new_node = malloc(sizeof(setnode_t));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = strdup(key);
    new_node->item = item;
    new_node->next = set->head;
    set->head = new_node;
    return true;
}

// Find an item by key in the set
void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }

    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->item;
        }
    }
    return NULL;
}

// Print the set
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return;
    }
    if (set == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (itemprint != NULL) {
            (*itemprint)(fp, node->key, node->item);
        }
    }
}

// Iterate over the set
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set == NULL || itemfunc == NULL) {
        return;
    }
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        (*itemfunc)(arg, node->key, node->item);
    }
}

// Delete the set
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return;
    }
    setnode_t *node = set->head;
    while (node != NULL) {
        setnode_t *next = node->next;
        if (set->call_itemdelete && itemdelete != NULL) {
            (*itemdelete)(node->item);
        }
        free(node->key);
        free(node);
        node = next;
    }
    free(set);
}

bool set_remove(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return false;
    }

    setnode_t *current = set->head;
    setnode_t *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                set->head = current->next;
            } else {
                previous->next = current->next;
            }
            
            free(current->key);
            if (set->call_itemdelete) {
                free(current->item);
            }
            free(current);

            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}
