#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Type-definition

// hash_bucket is used to store every key-value pair in map
// a hash_bucket always belong to a hash_slot
struct hash_bucket {
	const char* key;
	void* value;
	struct hash_bucket* next;
};
typedef struct hash_bucket* hash_bucket_t;

// hash_slot is used to store key-value pairs which has same hashcode
// a hash_slot can have multiple buckets in it.
struct hash_slot {
	struct hash_bucket* bucket;
};
typedef struct hash_slot* hash_slot_t;

// hashmap
struct hashmap {
	struct hash_slot* slots;
	size_t capacity;
	size_t mem_used;
};


static unsigned long
hashcode(const char* key) {
	if (key == NULL)
		return 0U;

	register unsigned long hash = 0U;
	unsigned long ch = 0U;
	while ((ch = (unsigned long)*key++) != 0) {
		hash = hash * 131 + ch;
	}
	return hash;
}

static unsigned long
hash(const char* key, size_t capacity) {
	return hashcode(key) % capacity;
}


hashmap_t
hashmap_init(size_t capacity) {
	if (capacity == 0) {
		return NULL;
	}

	hashmap_t hmap = NULL;
	hmap = (hashmap_t)malloc(sizeof(struct hashmap));
	if (hmap == NULL) {
		return NULL;
	}

	hmap->capacity = capacity;
	hmap->mem_used = sizeof(struct hashmap);

	size_t slot_size = capacity * sizeof(struct hash_slot);
	hmap->slots = (hash_slot_t)malloc(slot_size);
	if (hmap->slots == NULL) {
		return NULL;
	}
	hmap->mem_used += slot_size;
	memset(hmap->slots, 0, slot_size);
    
    return hmap;
}

int
hashmap_put(hashmap_t hmap, const char* key, void* value) {

	if (hmap == NULL || key == NULL) {
		return -1;
	}

	hash_bucket_t nbucket = (hash_bucket_t)malloc(sizeof(struct hash_bucket));
	if (nbucket == NULL) {
		return -1;
	}

	nbucket->key   = key;
	nbucket->value = value;
	nbucket->next  = NULL;

	size_t slot_index = hash(key, hmap->capacity);
	hash_bucket_t bucket = hmap->slots[slot_index].bucket;
	while (bucket != NULL) {
		if (!strcmp(key, bucket->key)) {
			bucket->value = value;
			return 0;
		}
		bucket = bucket->next;
	}
	nbucket->next = hmap->slots[slot_index].bucket;
	hmap->slots[slot_index].bucket = nbucket;
	hmap->mem_used += sizeof(struct hash_bucket);
		
	return 0;
}

void*
hashmap_get(hashmap_t hmap, const char* key) {
	if (hmap == NULL || key == NULL) {
		return NULL;
	}

	size_t slot_index = hash(key, hmap->capacity);
	hash_bucket_t bucket = hmap->slots[slot_index].bucket;

	while (bucket != NULL) {
		if (!strcmp(key, bucket->key)) {
			return bucket->value;
		}
		bucket = bucket->next;
	}

	return NULL;
}

void
hashmap_del(hashmap_t hmap, const char* key) {
	if (hmap == NULL || key == NULL) {
		return;
	}
	
	size_t slot_index = hash(key, hmap->capacity);
	hash_bucket_t bucket = hmap->slots[slot_index].bucket;
	hash_bucket_t previous = bucket;

	while (bucket != NULL) {
		if (!strcmp(key, bucket->key)) {
			if (bucket == hmap->slots[slot_index].bucket) {
				hmap->slots[slot_index].bucket = bucket->next;
			}
			previous->next = bucket->next;
			free(bucket);
			hmap->mem_used -= sizeof(struct hash_bucket);
			return;
		}
		previous = bucket;
		bucket = bucket->next;
	}
}

void
hashmap_foreach(hashmap_t hmap, hashmap_traversal_t callback) {
	if (hmap == NULL || callback == NULL) {
		return;
	}

	for (size_t slot = 0; slot < hmap->capacity; ++slot) {
		if (hmap->slots[slot].bucket != NULL) {
			hash_bucket_t bucket = hmap->slots[slot].bucket;
			while (bucket != NULL) {
				callback(bucket->key, bucket->value);
				bucket = bucket->next;
			}
		}
	}
}

void
hashmap_destory(hashmap_t hmap) {
	if (hmap == NULL) {
		return;
	}

	for (size_t i = 0; i < hmap->capacity; ++i) {
		hash_bucket_t bucket = hmap->slots[i].bucket;
		while (bucket != NULL) {
			hash_bucket_t tmp = bucket;
			bucket = bucket->next;
			if (tmp) free(tmp);
		}
	}
	free(hmap->slots);
	memset(hmap, 0, sizeof(struct hashmap));
	free(hmap);
}

size_t
hashmap_mem(hashmap_t hmap) {
	if (hmap == NULL)
		return 0;
	return hmap->mem_used;
}

void
hashmap_dump(hashmap_t hmap) {
	if (hmap == NULL)
		return;

	for (size_t i = 0; i < hmap->capacity; ++i) {
		if (hmap->slots[i].bucket != NULL) {
			printf("slot %lu:", i);
			hash_bucket_t bucket = hmap->slots[i].bucket;
			while (bucket != NULL) {
				printf("  ->|%s|", bucket->key);
				bucket = bucket->next;
			}
			printf("\n");
		}
	}
	printf("hashmap mem_used: [%lu]\n", hmap->mem_used); 
}

