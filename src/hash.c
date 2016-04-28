#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/hash.h"
#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261

/* Extremely simple FNV1 based hashtable.
 * No guarantees that it won't eat your children.
 */


typedef struct entry {
  char *key;
  void *val;
  struct entry *next;
} entry;

struct hashtable {
  unsigned long int size;
  entry **table;
};


int str_eq(char* a, char* b){
  int i = 0;
  while(a[i] == b[i]){
    if(a[i] == '\0')
      return 1;
    i++;
  }
  return 0;
}

entry* new_entry(char* key, void* val,entry* next){
  entry* e = (entry*) malloc(sizeof(entry));
  e->key = key; e->val = val; e->next = next;
  return e;
}

hashtable *ht_create(unsigned long int size){
  hashtable *h = (hashtable*) malloc(sizeof(hashtable));
  if(size < 1){
    h->size = 0;
    h->table = NULL;
  } else {
    h->size = size;
    h->table = (entry**) malloc(size * sizeof(entry*));
    for(int i = 0; i < size; i++ )
      h->table[i] = NULL;
  }
  return h;
}

/* FNV1 hash */
unsigned long int hash(char* key){
  unsigned long int hashval = FNV_OFFSET;
  int i = 0; char c = key[i];
  while(c != '\0'){
    hashval *= FNV_PRIME;
    hashval ^= key[i];
    c = key[++i];
  }
  return hashval;
}

entry* entry_get(entry* e, char* key){
  if(e == NULL){
    return NULL;
  } else if(str_eq(key, e->key)) {
    return e;
  } else {
    entry* prev = e;
    entry* cur = e->next;
    while(cur != NULL){
      if(str_eq(key, cur->key)){
	prev->next = cur->next;
	cur->next = e;
	return cur;
      }
      prev = cur;
      cur = cur->next;
    }
    return NULL;
  }
}

entry* entry_ins(entry* e, char* key,void* val){
  entry* res = entry_get(e,key);
  if(res == NULL) return new_entry(key,val,e);
  else{
    res->val = val;
    return res;
  }
}


void print_entry(entry* cur,unsigned long int h){
  entry *e = cur;
  printf("[Hash: %u]\n",h);
  printf("val of \"%s\" is %s\n", e->key,e->val);
  e=e->next;
}


void* ht_get(hashtable* h, char* key){
  unsigned long int hashval;
  hashval = hash(key);
  hashval = hashval % h->size;
  entry* e = entry_get(h->table[hashval],key);
  if(e == NULL)
    return NULL;
  else {
    h->table[hashval] = e;
    return e->val;
  }
}


void* ht_set(hashtable* h, char* key,void* val){
  unsigned long int hashval;
  hashval = hash(key);
  hashval = hashval % (h->size);
  entry* e = entry_ins(h->table[hashval],key,val);
  h->table[hashval] = e;
  return e;
}

void entry_delete(entry* e){
  entry* cur = e; entry* prev = NULL;
  while(cur != NULL){
    prev = cur;
    cur = cur->next;
    free(cur);
  }
}
void* ht_delete(hashtable* h){
  unsigned long int size = h->size;
  for(int i=0;i < size;i++)
    if(h->table[i] != NULL)
      entry_delete(h->table[i]);
  free(h);
}
