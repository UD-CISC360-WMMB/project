#ifndef GRAPH_H
#define GRAPH_H

typedef struct node {
  int tag;
  int color;
  int degree;
  int boundary;
  struct node **v;
} node;

typedef struct graph {
  int size;
  node **v;
} graph;

typedef struct subgraph {
  int size;
  int boundary;
  node **v;
} subgraph;


node*   new_node();
void    set_num_neighbors(node* nd, int i);
void    add_connection(node* nd1, int pos, node* nd2);
graph*  new_graph(node** nds,int size);
subgraph* new_subgraph(node** nds, int size);

graph*  rand_graph(int size, int connection);
void    print_graph(graph* g);
void print_subgraph(subgraph* sg);

subgraph** partition_graph(graph* g, int p_size);
void color_subgraph(subgraph* sg);

#endif
