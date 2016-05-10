#include "graph.h"

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
