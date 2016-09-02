#include "hashmap.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


bucket* hashmap_init() {
    bucket *map = (hashmap_t)malloc(sizeof(bucket) * CAPACITY);
    for (int i = 0; i < CAPACITY; ++i ) {
         map[i].position = NULL;
    }
    return map;
}

void hashmap_destory(bucket *map) {
    for (int i = 0; i < CAPACITY; ++i) {
        entry *ptr = map[i].position;
        while (ptr != NULL) {
            entry *head = ptr;
            ptr = ptr->next;
            if (ptr) free(head);
        }
    }
    free(map);
}

static unsigned long hashcode(char *key) {
    register unsigned long hash = 0;
    unsigned long ch;
    while (ch = (unsigned long)*key++) {
        hash = hash * 131 + ch;
    }
    return hash;
}

static int hash(char *key) {
    return hashcode(key) % CAPACITY;
}

void hashmap_put(bucket *map, char *key, void *value) {
    assert(map != NULL);
    int pos = hash(key);
    //printf("pos: %d\n", pos);
    entry *ptr = map[pos].position;

    entry *pnode = (entry *)malloc(sizeof(entry));
    pnode->key = key;
    pnode->ptrEntry = value;
    pnode->next = NULL;
    if (ptr == NULL) {
        map[pos].position = pnode;
    } else {
        while (ptr != NULL) {
            if (!strcmp(key, ptr->key)) {
                ptr->ptrEntry = value;
                return;
            }
            ptr = ptr->next;
        }
        //solve the bucket conflict
        pnode->next = map[pos].position;
        map[pos].position = pnode;
    }
}

void *hashmap_get(bucket *map, char *key) {
    assert(map != NULL);
    int pos = hash(key);
    entry *ptr = map[pos].position;

    while (ptr != NULL) {
        if (!strcmp(key, ptr->key)) {
            return ptr->ptrEntry;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void hashmap_remove(bucket *map, char *key) {
    assert(map != NULL);
    int pos = hash(key);
    entry *ptr = map[pos].position;
    entry *pre = ptr;

    if (ptr->next == NULL) {
        free(ptr);
        map[pos].position = NULL;
        return;
    }
    while (ptr != NULL) {
        if (!strcmp(key, ptr->key)) {
            pre->next = ptr->next;
            free(ptr);
            return;
        }
        pre = ptr;
        ptr = ptr->next;
    }
}

void hashmap_dump(bucket *map) {
    int i;
    for (i = 0; i < CAPACITY; i++) {
        if (map[i].position != NULL) {
            printf("bucket %d:  ", i);
            entry *ptr = map[i].position;
            while (ptr != NULL) {
                printf(" ->|%s|", ptr->key);
                ptr = ptr->next;
            }
            printf("\n");
        }
    }
}

