#include <stdio.h>
#include <stdlib.h>
#include "../src/graph.h"

int main(){
  graph* g;

  g = rand_graph(8);
  print_graph(g);
    
  return 0;
}
