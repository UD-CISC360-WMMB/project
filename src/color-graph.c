#include "graph.h"
#include <stdio.h>

void sequential_color(graph* g) {
	for (int i = 0 ; i < g->size; i++ ) {
		node* curr = g->v[i];
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

void color_subgraph(p_graph pg, int index){
  int size = pg.sub_size;
  node** sub = pg.subs[index];
	for (int i = 0; i < size; i++) {
		node* curr = sub[i];
		int fcolor = 0;
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

int detect_conflicts(node* nd){
  int color = nd->color, conflict = 0,degree = nd->degree;
  int tag = nd->tag;
  for(int i=0;i < degree;i++){
    if(nd->v[i]->color == color /*&& nd->v[i]->tag <= tag */){
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
