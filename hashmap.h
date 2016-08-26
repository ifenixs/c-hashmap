#ifndef HASHMAP_H
#define HASHMAP_H

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

typedef bucket * hashmap;


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
hashmap_destory(bucket *map);


#endif
