#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/graph.h"

int main(int argc, char *argv[]){
	graph* g;
	subgraph ** sgs;
  partition p;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);

	g = rand_graph(size, connections);
	print_graph(g);
	p = partition_graph(g,5);
//	validate_color(g);
  for(int i=0;i<p.num_subs;i++)
    color_subgraph(p.subs[i]);
//	validate_color(g);
//	color_boundary(g);
//	sequential_color(g);
//	validate_color(g);
//	print_subgraph(p.subs[0]);
  print_partition(p);
  //	print_subgraph(sgs[1]);
	return 0;
}
