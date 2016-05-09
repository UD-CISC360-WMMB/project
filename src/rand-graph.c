#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "./graph.h"

int** randMat( int size ) {
	int* values		= calloc(size*size, sizeof(int));
	int** adjMat	= malloc(size*sizeof(int*));
	srand(time(NULL));
	int arrayPt;
	for (int i=0; i < size ; i++) {
		adjMat[i]	=	values + i*size;
	}
	for (int i = 0 ; i < size; i++ ) {
		int i = (int) (size * ((double) rand() / (RAND_MAX +1.0)));
		int j = (int) (size * ((double) rand() / (RAND_MAX +1.0)));
		while (i == j) {
			j = (int) (size * ((double) rand() / (RAND_MAX +1.0)));
		}
		adjMat[i][j] = 1;
		adjMat[j][i] = 1;
	}
	return adjMat;
}

graph* rand_graph(int size)  {
	int ** randmat = randMat(size);
	node** nodes = malloc(size*sizeof(node));
	for (int i = 0 ; i < size ; i++) {
		nodes[i] = new_node();
		int neighbors = 0;
		for (int j = 0 ; j < size ; j++) {
			if (randmat[i][j] == 1) {
				neighbors++;
			}
		}
		set_num_neighbors(nodes[i], neighbors);
	}
	for (int i = 0 ; i < size ; i++) {
		int currNeighbor = 0;
		for (int j = 0 ; j < size ; j++) {
			if (randmat[i][j] == 1) {
				add_connection(nodes[i], currNeighbor, nodes[j]);
				currNeighbor++;
			}
		}
	}
	return new_graph(nodes, size);
}
