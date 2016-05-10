#include "graph.h"

void	sequential_color(graph* g) {
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
