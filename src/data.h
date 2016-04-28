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

#endif
