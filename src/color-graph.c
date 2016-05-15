#include "graph.h"
#include <stdio.h>

void sequential_color(graph* g) {
	for (int i = 0 ; i < g->size ; i++ ) {
		node* curr = g->v[i];
		int fcolor = 0 ;
		for (int j = 0 ; j < g->size ; j++ ) {
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

//void color_subgraph(node** sub, int size){
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

