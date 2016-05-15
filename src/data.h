#ifndef DATA_H
#define DATA_H
#define cons(X,Y) new_list((void *) X, Y)

typedef struct list{
  void *data;
  struct list *next;
} list;

typedef struct stack{
  list *top;
} stack;

typedef struct queue{
  int size;
  list *first;
  list *last;
} queue;


list  *new_list(void*,list*);
void  dest_list(list *);
stack *new_stack();
queue *new_queue();
void  *pop(stack *s);
void  push(void* data, stack *s);
void  enqueue(void *data,queue *q);
void  *dequeue(queue *q);
void  **dequeue_to_array(queue *q);


typedef struct hashtable hashtable;
hashtable *ht_create(unsigned long int size);
void* ht_get(hashtable* h, char* key);
void* ht_set(hashtable* h, char* key,void* val);
void* ht_delete(hashtable* h);


#endif
