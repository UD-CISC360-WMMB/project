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
subgraph* new_subgraph(node** nds, int size){
  subgraph* s = (subgraph*) malloc(sizeof(subgraph));
  s->size = size;
  s->v = nds;
  return s;
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

void print_subgraph(subgraph* sg){
  int size  = sg->size;
  node** nds = sg->v;
  for(int i=0; i < size; i++){
    node* nd = nds[i];
    node** v = nd->v;
    int degree = nd->degree;
    printf("%d (color: %d): ", nd->tag, nd->color);
    for(int j=0; j < degree; j++)
      printf("%d, ", v[j]->tag);
    printf("\n");
  }
}

void validate_color(graph* g) {
	int valid = 1;
	for (int i = 0 ; i < g->size ; i++ ) {
		node* currNode = g->v[i];
		int currColor = currNode->color;
		int boundary = currNode->degree;
		for (int j = 0 ; j < boundary ; j++ ) {
			int colorCheck = currNode->v[j]->color;
			if (colorCheck == currColor) {
				valid = 0 ;
				printf("Validation failed at node %d\n", currNode->tag);
			}
		}
	}
	if (valid == 1) {
		printf("%s", "Validation successful\n");
	}
}
