#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "../src/graph.h"

int min; // minimum size
int max; // maximum size
graph* g; // graph
subgraph** sg; // graph partitions
// FILE* file; // stores performance values from min to max


void graph_eval(int size){
  min = 0;
  max = 0;

  //file = fopen("evals.txt", "r");
  g = rand_graph(size);
  // need to cilk and stuff
  double subgraph_size = g->size; // divide by threads
  int s = (int) subgraph_size;
  sg = partition_graph(g, s);

  // time this and thread and stuff
  clock_t start = clock();
  for(int j = 0; j < s; j++){
    color_subgraph(sg[j]);
  }
  clock_t end = clock();

  // write to file for data graphing
  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Hi. %.3f",duration);
  //fputs(string, file);
  //fputs("\n", file);
  // display number of colors, go through graph, find max color



  //fclose(file);
}


int main(){
  graph_eval(10);
}
