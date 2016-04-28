#include "graph.h"

void	color(subgraph* sg) {
	int banned[sg->size];
	for (int i = 0 ; i < sg->size ; i++ ) {
		banned[i] = 0 ;
	}
	for (int i = 0 ; i < sg->size ; i++ ) {
		node* curr = sg->v[i];
		int banCount = 0;
		int fcolor = 0 ;
		for (int j = 0 ; i < sg->size ; i++ ) {
			if ( j != i ) {
				node* currCheck = sg->v[j];
				int found = 0;
				for (int k = 0 ; k < currCheck->degree ; k++) {
					if (currCheck->v[k] == curr) {
						found = 1;
						k = currCheck->degree;
					}
				}
				if (found != 0 ) {
					banned[banCount] = currCheck->color;
					banCount++;
				}
			}
		}
		for (int j = 0 ; j < banCount ; j++) {
			if (fcolor == banned[j]) {
				fcolor++;
			}
		}
		curr->color = fcolor;
	}
}
