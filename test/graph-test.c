#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/graph.h"

int main(int argc, char *argv[]){
	graph* g;
	subgraph ** sgs;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);

	g = rand_graph(size, connections);
	print_graph(g);
//	sgs = partition_graph(g,6);
//	validate_color(g);
//	color_subgraph(sgs[0]);
//	color_subgraph(sgs[1]);
//	validate_color(g);
//	color_boundary(g);
	sequential_color(g);
	validate_color(g);
//	print_subgraph(sgs[0]);
//	print_subgraph(sgs[1]);
	return 0;
}
