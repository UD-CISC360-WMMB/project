#include "graph.h"
#include <stdio.h>

/*
int min_color(node* nd){
  int degree = nd->degree;
  int color=0;
  while(1){
    int found = 1;
    for(int i=0;i < degree; i++)
      if(nd->v[i]->color == color){
        found = 0;
        color++;
        break;
      }
    if(found)
      return color;
  }
}

int min_color_in_sub(node* nd,int subgraph){
  int degree = nd->degree;
  int color=0;
  while(1){
    int found = 1;
    for(int i=0;i < degree; i++){
      node* neighbor = nd->v[i];
      if(neighbor->subgraph == subgraph && neighbor->color == color){
        found = 0;
        color++;
        break;
      }
    }
    if(found)
      return color;
  }
}



void sequential_color(graph* g){
  int size = g->size;
  node** v = g->v;
  for(int i=0; i < size; i++){
    node* nd = v[i];
    if(nd->color < 0)
      nd->color = min_color(nd);
  }
}



void subgraph_color(node** sub, int size){
  int subgraph = sub[0]->subgraph;
  for(int i=0; i < size; i++){
    node* nd = sub[i];
    if(nd->color < 0)
      nd->color = min_color_in_sub(nd,subgraph);
  }
}
*/




void sequential_color(graph* g) {
	for (int i = 0 ; i < g->size; i++ ) {
		node* curr = g->v[i];
    if(curr->color < 0){
      int fcolor = 0;
      for (int j = 0; j < g->size; j++ ) {
        if ( j != i ) {
          node* currCheck = g->v[j];
          int found = 0;
          for (int k = 0 ; k < currCheck->degree ; k++) {
            if (currCheck->v[k]->tag == curr->tag) {
              found = 1;
              k = currCheck->degree;
            }
          }
          if (found != 0 ) {
            if (currCheck->color >= fcolor) {
              fcolor = (currCheck->color) + 1;
            }
          }
        }
      }
      curr->color = fcolor;
    }
	}
}


void color_subgraph(p_graph pg, int index){
  int size = pg.sub_size;
  node** sub = pg.subs[index];
  int sub_id = sub[0]->subgraph;
	for (int i = 0; i < size; i++) {
		node* curr = sub[i];
		int fcolor = 0;
    if(curr->color < 0){
      for (int j = 0; j < size; j++) {
        if (j != i) {
          node* currCheck = sub[j];
          int found = 0;
          for (int k = 0 ; k < currCheck->degree; k++) {
            if (currCheck->v[k]->tag == curr->tag) {
              found = 1;
              k = currCheck->degree;
            }
          }
          if (found != 0 ) {
            if (currCheck->color >= fcolor) {
              fcolor = (currCheck->color) + 1;
            }
          }
        }
      }
      curr->color = fcolor;
    }
	}
}


int detect_conflicts(node* nd){
  int color = nd->color, conflict = 0,degree = nd->degree;
  int tag = nd->tag;
  for(int i=0;i < degree;i++){
    if(nd->v[i]->color == color && nd->tag <= nd->v[i]->tag){
      nd->color = -1;
      conflict = 1;
    }
  }
  return conflict;
}

void detect_all_conflicts(boundary_table *bt){
  int size = bt->size;
  node** bnds = bt->nodes;
  int* conflicts = bt->conflicts;
  
  for(int i=0; i < size;i++){
    if(conflicts[i])
      conflicts[i] = detect_conflicts(bnds[i]);
  }
}

int count_conflicts(boundary_table *bt){
  int size = bt->size, count = 0;
  int* conflicts = bt->conflicts;
  for(int i=0; i < size;i++)
    if(conflicts[i])
      count++;
  return count;
}


void color_boundary(graph* g) {
	for (int i ; i < g->size ; i++) {
		node* curr = g->v[i];
		int minColor = 0;
		for (int j = 0 ; j < curr->degree ; j++) {
			if (curr->v[j]->color == minColor) {
				minColor++;
			}
		}
		curr->color = minColor;
	}
}
