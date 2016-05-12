#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <pthread.h>
#include <math.h>
#include "../src/graph.h"

int main(int argc, char *argv[]){
	graph* g;
	subgraph ** sgs;
  partition p;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);

	g = rand_graph(size, connections);
	print_graph(g);
	// appropriately size partitions by workers and proper division
	int p_size = g->size / __cilkrts_get_nworkers();
	int x_size = p_size;
	int remainder = g->size % p_size;
	while(remainder > 0){
		x_size--;
		remainder = g->size % x_size;
	}

	printf("g_size, %d, x_size: %d, remainder %d\n", g->size, x_size, remainder);
	p = partition_graph(g, x_size);

	int subs = p.num_subs;
	int workers = __cilkrts_get_nworkers();
	double subsD = (double) subs;
	double workersD = (double) workers;
	double gsD =  ceil(subsD / workersD);
	int gs = (int) gsD;
	#pragma grainsize = gs;
	printf("subs: %d, workers: %d, subs/gs: %d\n", subs, workers, gs);
	// parallel coloring through cilk
  cilk_for(int i = 0; i < gs; i++){
		for(int j = i*subs; j < i*subs + gs; j++){
			color_subgraph(p.subs[i]);
		}
	}
	 //validate_color(g);
	//color_boundary(g);
	//sequential_color(g);
	//validate_color(g);
  for(int s = 0; s < p.num_subs; s++){
	   print_subgraph(p.subs[s]);
  }
  print_partition(p);
  	//print_subgraph(sgs[1]);
	return 0;
}
