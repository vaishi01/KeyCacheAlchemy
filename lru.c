#include "lru.h"
#include "set.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static lru_node_t *lru_node_new(const char *key, void *item) {
    if (!key) return NULL;

    lru_node_t *node = malloc(sizeof(lru_node_t));
    if (!node) return NULL;

    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }

    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static void lru_remove_node(lru_t *lru, lru_node_t *node) {
    if (!node || !lru) return;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        lru->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        lru->tail = node->prev;
    }

    node->next = NULL;
    node->prev = NULL;
    lru->size--;
}

static void lru_delete_node(lru_node_t *node, void (*itemdelete)(void *)) {
    if (!node) return;

    if (itemdelete && node->item) {
        itemdelete(node->item);
    }
    free(node->key);
    free(node);
}

/*
static void lru_move_to_front(lru_t *lru, lru_node_t *node) {
    if (!lru || !node || lru->head == node) return;
    lru_remove_node(lru, node);
    
    if (lru->head == NULL) {
        lru->head = node;
        lru->tail = node;
        return;
    }

    lru->head->prev = node;
    node->next = lru->head;
    node->prev = NULL;
    lru->head = node;
}
*/

 static void lru_move_to_front(lru_t *lru, lru_node_t *node) {
    if (!lru || !node || lru->head == node) return;

    if (lru->head == node) {
        return;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (lru->tail == node) {
        lru->tail = node->prev;
    }
    node->prev = NULL;
    node->next = lru->head;
    lru->head->prev = node;
    lru->head = node;
}


lru_t *lru_new(int capacity) {
    if (capacity <= 0) return NULL;

    lru_t *lru = malloc(sizeof(lru_t));
    if (!lru) return NULL;

    lru->capacity = capacity;
    lru->size = 0;
    lru->head = lru->tail = NULL;
    lru->hash_table = hashtable_new(capacity);

    if (!lru->hash_table) {
        free(lru);
        return NULL;
    }

    return lru;
}

void lru_print(lru_t *lru, FILE *fp, void (*itemprint)(FILE *, const char *, void *)) {
    if (!lru || !fp || !itemprint) return;

    for (lru_node_t *node = lru->head; node; node = node->next) {
        itemprint(fp, node->key, node->item);
    }
}

bool lru_insert(lru_t *lru, const char *key, void *item) {
    if (lru == NULL || key == NULL || item == NULL) {
        return false;
    }

    lru_node_t *node = hashtable_find(lru->hash_table, key);
    if (node != NULL) {
        lru_move_to_front(lru, node);
        return false;
    }

    if (lru->size >= lru->capacity) {
        lru_node_t *old_tail = lru->tail;
        if (!old_tail) {
            //lru_node_t *old_tail;
            old_tail = lru->head;
            for (int i = 0; i < lru->capacity; i++){
                if (old_tail->next!= NULL){
                    old_tail = old_tail->next;
                }
            }
        }
        lru_remove_node(lru, old_tail);
        hashtable_remove(lru->hash_table, old_tail->key);
        //free(old_tail->key);
        //free(old_tail);
        lru->size--;
    }

    lru_node_t *new_node = lru_node_new(key, item);
    if (!new_node) {
        return false;
    }
    
    if (lru->head == NULL) {
        lru->head = new_node;
        lru->tail = new_node;
    } else {
        lru->head->prev = new_node;
    new_node->next = lru->head;
    new_node->prev = NULL;
    lru->head = new_node;
    }

    //lru_move_to_front(lru, new_node);

    bool inserted = hashtable_insert(lru->hash_table, key, new_node);
    if (!inserted) {
        return false;
    }

    hashtable_insert(lru->hash_table, key, new_node);
    lru->size++;
    return true;
}

void *lru_find(lru_t *lru, const char *key) {
    if (!lru || !key) return NULL;
    lru_node_t *node = hashtable_find(lru->hash_table, key);
    if (node) {
        lru_move_to_front(lru, node);
        return node->item;
    }

    return NULL;
}

/*
void lru_print(lru_t *lru, FILE *fp, void (*itemprint)(FILE *, const char *, void *)) {
    if (!lru || !fp || !itemprint) return;

    for (lru_node_t *node = lru->head; node; node = node->next) {
        itemprint(fp, node->key, node->item);
    }
}
*/

void lru_iterate(lru_t *lru, void *arg, void (*itemfunc)(void *, const char *, void *)) {
    if (!lru || !itemfunc) return;

    for (lru_node_t *node = lru->head; node; node = node->next) {
        itemfunc(arg, node->key, node->item);
    }
}

void lru_delete(lru_t *lru, void (*itemdelete)(void *)) {
    if (!lru) return;
    lru_node_t *node = lru->head;
    while (node) {
        lru_node_t *next = node->next;
        lru_delete_node(node, itemdelete);
        node = next;
    }
    lru->size--;
    hashtable_delete(lru->hash_table, NULL);
    free(lru);
}
