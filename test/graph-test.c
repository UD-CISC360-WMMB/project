
#include <stdio.h>
#include <stdlib.h>
#include "../src/graph.h"

int main(){
  graph* g;
  subgraph ** sgs;

  g = rand_graph(8);
  print_graph(g);
  sgs = partition_graph(g,2);
  color_subgraph(sgs[0]);
  return 0;
}
