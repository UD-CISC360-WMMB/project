#include "./data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261


/* Definition of data structures */

list *new_list(void *data, list *next){
  list *lst = (list *) malloc(sizeof(list));
  lst->data = data; lst->next = next;
  return lst;
}

void dest_list(list *lst){
  while(lst != NULL){
    list *next = lst->next;
    free(lst);
    lst = next;
  }
}

stack *new_stack(){
  stack *s = (stack*) malloc(sizeof(stack));
  s->top = NULL;
  return s;
}

queue *new_queue(){
  queue *q = (queue*) malloc(sizeof(stack));
  q->size = 0;
  q->first = NULL;
  q->last = NULL;
  return q;
}

void *pop(stack *s){
  list *old = s->top;
  s->top = old->next;
  return old->data;
}

void push(void* data, stack *s){
  s->top = cons(data, s->top);
}

void enqueue(void *data,queue *q){
  list *lst = cons(data,NULL);
  if(q->size <= 0){
    q->first = lst;
    q->last = lst;
  } else {
    q->last->next = lst;
    q->last = lst;
  }
  q->size = q->size + 1;
}

void *dequeue(queue *q){
  void *data;
  if(q->size <= 0){
    data = NULL;
  } else {
    data = q->first->data;
    q->first = q->first->next;
    q->size = q->size - 1;
  }
  return data;
}

void **dequeue_to_array(queue *q){
  int len = q->size;
  list *lst = q->first;
  void **a = (void **)malloc(len * sizeof(void*));
  for(int i = 0; i < len; i++)
    a[i] = dequeue(q);
  return a;
}


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
