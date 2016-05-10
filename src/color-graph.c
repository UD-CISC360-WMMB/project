#include "graph.h"
#include <stdio.h>

void	color_subgraph(subgraph* sg) {
	for (int i = 0 ; i < sg->size ; i++ ) {
		node* curr = sg->v[i];
		int fcolor = 0 ;
		for (int j = 0 ; j < sg->size ; j++ ) {
			if ( j != i ) {
				node* currCheck = sg->v[j];
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
//					printf("Lowest Allowed Color:%d \n", fcolor);
				}
			}
		}
		curr->color = fcolor;
	}
}
