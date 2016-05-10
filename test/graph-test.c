#include <stdio.h>
#include <stdlib.h>
#include "../src/graph.h"

int main(){
	graph* g;
	subgraph ** sgs;

	g = rand_graph(8);
	print_graph(g);
	sgs = partition_graph(g,4);
	print_subgraph(sgs[0]);
	print_subgraph(sgs[1]);
	for (int i = 0 ; i < 2 ; i++ ) {
//		printf("%d", sgs[i]->v[0]->degree);
	}
//	color_subgraph(sgs[0]);
//	color_subgraph(sgs[1]);
	return 0;
}
