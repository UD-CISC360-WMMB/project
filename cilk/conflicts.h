#ifndef CONFLICTS_H
#define CONFLICTS_H


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

int detect_conflictsx(node* nd);
int detect_all_conflictsx(boundary table *bt);
