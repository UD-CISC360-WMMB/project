#include <stdlib.h>

typedef struct al_node {
  int degree;
  int degree_in;
  int color;
  struct al_node *adj[];
} al_node;


typedef struct al_graph {
  int size;
  al_node *v[];
} al_graph;



typedef struct {
  int color;
  int data;
} am_node;

typedef struct am_graph {
  int size;
  am_node **rows;
}

typedef struct al_subgraph {
  int size_in;
  int boundary;
  al_node *v[];
} al_subgraph;




