#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/graph.h"

int main(int argc, char *argv[]){
	graph* g;
  p_graph pg;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);
  
	g = rand_graph(size, connections);
  
	print_graph(g);
  //pg = block_partition(g,5);
  pg = dfs_partition(g,5);
  
  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);
  color_boundary(g);
  
  print_subgraphs(pg);

  sequential_color(g);
  validate_color(g);

	return 0;
}
