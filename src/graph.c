#include <stdlib.h>
#include <stdio.h>
#include "./graph.h"

int node_count=0;

node* new_node() {
  node* nd = (node*) malloc(sizeof(node));
  nd->tag = node_count;
  node_count++;
  return nd;
}


void set_num_neighbors(node* nd, int size){
  node** nds = (node**) malloc(size * sizeof(node*));
  nd->degree = size;
  nd->v = nds;
}

void add_connection(node* nd1, int pos, node* nd2){
  nd1->v[pos] = nd2;
}

graph* new_graph(node** nds, int size){
  graph* g = (graph*) malloc(sizeof(graph));
  g->size = size;
  g->v = nds;
  return g;
}

void print_graph(graph* g){
  int size  = g->size;
  node** nds = g->v;
  for(int i=0; i < size; i++){
    node* nd = nds[i];
    node** v = nd->v;
    int degree = nd->degree;
    printf("%d: ", nd->tag);
    for(int j=0; j < degree; j++)
      printf("%d, ", v[j]->tag);
    printf("\n");
  }
}

