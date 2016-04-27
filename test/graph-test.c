#include <stdio.h>
#include <stdlib.h>
#include "../src/graph.h"

int main(){
  graph* g;

  printf("Hello!\n");
  g = rand_graph(8);
  print_graph(g);
  


  
  return 0;
}
