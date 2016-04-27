#include <stdio.h>
#include "../src/graph.h"

int main(){
  graph* g = rand_graph(8);
  tag_graph(g);
  print_graph(g);
  return 0;
}
