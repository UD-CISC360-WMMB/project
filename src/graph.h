#ifndef GRAPH_H
#define GRAPH_H
#define node al_node
#define graph al_graph
#define subgraph al_subgraph

typedef struct al_node {
  int degree;
  int degree_in;
  int color;
  struct al_node **adj;
} al_node;

typedef struct al_graph {
  int size;
  al_node **v;
} al_graph;

typedef struct al_subgraph {
  int size_in;
  int boundary;
  al_node **v;
} al_subgraph;


node*   new_node();
void    set_num_neighbors(node* nd, int i);
void    add_connection(node* nd1, int pos, node* nd2);
graph*  new_graph(node* nds,int size);
graph*  random_graph(int size);

#endif
