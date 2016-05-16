#include "graph.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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


void sequential_resolve(graph* g){
  int size = g->size;
  node** v = g->v;
  for(int i=0; i < size; i++){
    node* nd = v[i];
    if(nd->color < 0)
      nd->color = min_color(nd);
  }
}


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
    if(nd->v[i]->color == color && (rand()%2) ){
      nd->color = -1;
      conflict = 1;
    }
  }
  return conflict;
}

int detect_all_conflicts(boundary_table *bt){
  int size = bt->size;
  node** bnds = bt->nodes;
  int* conflicts = bt->conflicts;
  int count=0;
  srand(time(NULL));
  
  for(int i=0; i < size;i++){
    if(conflicts[i]){
      int dc = detect_conflicts(bnds[i]);
      count += dc;
      conflicts[i] = dc;
    }
  }
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
