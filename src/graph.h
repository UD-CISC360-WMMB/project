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


typedef struct p_graph {
  int num_subs;
  int sub_size;
  node*** subs;
} p_graph;


/*
typedef struct subgraph {
  int size;
  int boundary;
  node **v;
} subgraph;

typedef struct partition{
  subgraph** subs;
  int num_subs;
} partition;
*/

node*   new_node();
void    set_num_neighbors(node* nd, int i);
void    add_connection(node* nd1, int pos, node* nd2);
graph*  new_graph(node** nds,int size);
//subgraph* new_subgraph(node** nds, int size);

graph*  rand_graph(int size, int connection);
void    print_graph(graph* g);
//void print_subgraph(subgraph* sg);
//void print_partition(partition p);
void print_subgraphs(p_graph pg);

void validate_color(graph* g);

//partition partition_graph(graph* g, int p_size);
p_graph block_partition(graph* g, int sub_size);
p_graph dfs_partition(graph* g, int p_size);


//void color_subgraph(subgraph* sg);
//void color_subgraph(node** sub, int size);
void color_subgraph(p_graph pg, int index);
void color_boundary(graph* g);
void sequential_color(graph* g);

#endif
