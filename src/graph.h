#ifndef GRAPH_H
#define GRAPH_H

typedef struct node {
  int tag;
  int subgraph;
  int color;
  int degree;
  int degree_out;
  struct node **v;
} node;

typedef struct graph {
  int size;
  int num_subs;
  int sub_size;
  node **v;
} graph;

typedef struct boundary_table {
  node** nodes;
  int *conflicts;
  int size;
} boundary_table;

typedef struct p_graph {
  int num_subs;
  int sub_size;
  node*** subs;
  boundary_table *boundary_table;
} p_graph;


node*   new_node();
void    set_num_neighbors(node* nd, int i);
void    add_connection(node* nd1, int pos, node* nd2);
graph*  new_graph(node** nds,int size);

graph*  rand_graph(int size, int connection);
void    print_graph(graph* g);
void print_subgraphs(p_graph pg);

void validate_color(graph* g);


void label_boundary_nodes(p_graph *pg);
void collect_boundary_nodes(p_graph *pg);

p_graph block_partition(graph* g, int sub_size);
p_graph bfs_partition(graph* g, int p_size);

void color_subgraph(p_graph pg, int index);
void subgraph_color(node** sub, int size);

void color_boundary(graph* g);


int detect_all_conflicts(boundary_table *bt);
int count_conflicts(boundary_table *bt);
void sequential_color(graph* g);

#endif
