#include <stdio.h>
#include <stdlib.h>
#include "../src/graph.h"

int main(){
	graph* g;
	subgraph ** sgs;

	g = rand_graph(12, 15);
	print_graph(g);
	sgs = partition_graph(g,6);
//	print_subgraph(sgs[0]);
//	print_subgraph(sgs[1]);
	color_subgraph(sgs[0]);
	color_subgraph(sgs[1]);
	print_subgraph(sgs[0]);
	print_subgraph(sgs[1]);
	return 0;
}
