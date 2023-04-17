#ifndef _HASHMAP_H
#define _HASHMAP_H

// 
// FILE: hashmap.h
//
// @author ifenix fenice.suns@gmail.com
// 
// @brief A fixed-size hashmap which can store key-value pair of char* and void*
//
// Note: The key cannot be NULL

#include <stddef.h>

struct hashmap;
typedef struct hashmap* hashmap_t;

typedef void
(*hashmap_traversal_t)(const char* key, void* value);

hashmap_t
hashmap_init(size_t capacity);

int
hashmap_put(hashmap_t hmap, const char* key, void* value);

void*
hashmap_get(hashmap_t hmap, const char* key);

void
hashmap_del(hashmap_t hmap, const char* key);

void
hashmap_foreach(hashmap_t hmap, hashmap_traversal_t callback);

size_t
hashmap_mem(hashmap_t hmap);

void
hashmap_dump(hashmap_t hmap);

void
hashmap_destory(hashmap_t hmap);

#endif	// _HASHMAP_H
