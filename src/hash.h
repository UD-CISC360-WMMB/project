#ifndef HASH_H
#define HASH_H
typedef struct hashtable hashtable;
hashtable *ht_create(unsigned long int size);
void* ht_get(hashtable* h, char* key);
void* ht_set(hashtable* h, char* key,void* val);
void* ht_delete(hashtable* h);
#endif
