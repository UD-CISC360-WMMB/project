#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "./src/graph.h"

int min; // minimum size
int max; // maximum size
graph* g; // graph
subgraph** sg; // graph partitions
// FILE* file; // stores performance values from min to max


void graph_eval(int size){

  //file = fopen("evals.txt", "r");
  g = rand_graph(size, size);
  int subgraph_size = g->size;
  sg = partition_graph(g, subgraph_size);

  clock_t start = clock();
  for(int j = 0; j < subgraph_size; j++){
    //color_subgraph(sg[j]);
    print_subgraph(sg[j]);
  }
  clock_t end = clock();
  double duration = (end - start);
  printf("Time: %0.5f \n", duration);
}


int main(){
  graph_eval(10);
}
