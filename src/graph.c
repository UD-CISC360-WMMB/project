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
    if(degree){
      printf("%d: ", nd->tag);
      if(0 < degree)
        printf("%d", v[0]->tag);
      for(int j=1; j < degree; j++)
        printf(", %d", v[j]->tag);
      printf("\n");
    }
  }
}

void print_subgraphs(p_graph pg){
  for(int i=0; i < pg.num_subs;i++){
    printf("Subgraph %d:\n", i);
    for(int j=0; j < pg.sub_size; j++){
      node* nd = pg.subs[i][j];
      node** v = nd->v;
      int degree = nd->degree;
      if(degree){
        printf("  %d [color: %d, subgraph: %d, out degree: %d]: ",
               nd->tag, nd->color, nd->subgraph, nd->degree_out);
        if(0 < degree)
          printf("%d", v[0]->tag);
        for(int j=1; j < degree; j++)
          printf(", %d", v[j]->tag);
        printf("\n");
      }
    }
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
