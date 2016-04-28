#include "../include/data.h"
#include <stdlib.h>
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
  } else{
    q->last->next = lst;
    q->last = lst;
  }
  q->size = q->size + 1;
}

void *dequeue(queue *q){
  void *data;
  if(q->size <= 0)
    data = NULL;
  else{
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
