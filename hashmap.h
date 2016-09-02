#ifndef _HASHMAP_H
#define _HASHMAP_H

// capacity of bucket
#define CAPACITY 4097

typedef struct _entry{
    char *key;
    void *ptrEntry;
    struct _entry *next;
} entry;

typedef struct {
    entry *position;
} bucket;

typedef bucket * hashmap_t;


extern bucket *
hashmap_init();

static int
hash(char *key);

static unsigned long
hashcode(char *key);

extern void
hashmap_put(bucket *map, char *key, void *value);


extern void*
hashmap_get(bucket *map, char *key);

extern void
hashmap_remove(bucket *map, char *key);

extern void
hashmap_dump(bucket *map);

extern void
hashmap_destory(bucket *map);


#endif
