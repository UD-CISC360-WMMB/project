#include <stdio.h>
#include "../src/data.h"

int main(char *argv[]) {
  stack *s = new_stack();
  queue *q = new_queue();
  char *c[5] = {"tom","dick","harry","jerry","phil"};
  for(int i = 0; i < 5; i++){
    push((void*) c[i], s);
    enqueue((void*) c[i],q);
  }
  printf("\nQueue:\n");
  while(q->size != 0){
    printf("%s\n", (char*) dequeue(q));
  }
  printf("\nStack:\n");
  while(s->top != NULL){
    printf("%s\n",(char*) pop(s));
  }
  return 0;
}
