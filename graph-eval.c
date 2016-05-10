#include <stdio.h>
#include <cilk/cilk.h>
#include "graph.h"
#include <cilk/cilk_api.h>


int main(){
  int min = 10;
  int max = 1000;
  graph* g;
  subgraph** sg;

  for(int i = min; i < max; i++){
      g = rand_graph(i);
      // need to cilk and stuff
      double size = g->size / __cilkrts_get_nworkers(); // divide by threads
      int s = (int) size;
      sg = partition_graph(g, size);

      // time this and thread and stuff
      for(int j = 0; j < size; j++){
        color_subgraph(sg[j]);
      }

      // display number of colors, go through graph, find max color
  }
}
