#include <stdio.h>
#include "../src/data.h"

int main(char *argv[]) {
  stack *s = new_stack();
  queue *q = new_queue();
  hashtable *ht = ht_create(256);
  char *c[5] = {"tom","dick","harry","jerry","phil"};
  for(int i = 0; i < 5; i++){
    push(c[i], s);
    enqueue(c[i],q);
  }
  
  ht_set( ht, "apple",  "green" );
  ht_set( ht, "banana", "yellow" );
  ht_set( ht, "apple",  "yellow" );
  ht_set( ht, "orange", "orange" );
  ht_set( ht, "plum",   "purple" );
  ht_set( ht, "apple",  "red" );
  
  printf("=Queue=\n");
  while(q->size != 0)
    printf("%s\n", (char*) dequeue(q));
  
  printf("=Stack=\n");
  while(s->top != NULL)
    printf("%s\n",(char*) pop(s));

  printf("=Hash Table=\n");
  printf( "%s: %s\n","apple",  ht_get( ht, "apple" ) );
  printf( "%s: %s\n","banana", ht_get( ht, "banana" ) );
  printf( "%s: %s\n","orange", ht_get( ht, "orange" ) );
  printf( "%s: %s\n","plum",   ht_get( ht, "plum" ) );
  ht_delete(ht);
  return 0;
}
