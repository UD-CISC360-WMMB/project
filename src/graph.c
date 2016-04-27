#include <stdlib.h>
#include <stdio.h>
#include "./graph.h"

al_node* new_node() {
  al_node* nd = (al_node*) malloc(sizeof(al_node));
  return nd;
}

void set_num_neighbors(al_node* nd, int size){
  al_node** nds = (al_node**) malloc(size * sizeof(al_node*));
  nd->degree = size;
  nd->degree_in = 0;
  nd->v = nds;
}

void add_connection(al_node* nd1, int pos, al_node* nd2){
  nd1->v[pos] = nd2;
}

al_graph* new_graph(al_node** nds, int size){
  al_graph* g = (al_graph*) malloc(sizeof(al_graph));
  g->size = size;
  g->v = nds;
}

void tag_graph(graph* g){
  int size  = g->size;
  node** nds = g->v;
  for(int i=0;i < size; i++){
    node* nd = nds[i];
    nd->tag = i;
  }
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
