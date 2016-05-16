#include <stdlib.h>
#include <stdio.h>
#include <cilk/cilk.h>
#include <pthread.h>
#include <../src/project.a>

pthread_mutex_t m; // lock

int detect_conflictsx(node* nd){
  int color = nd->color, conflict = 0,degree = nd->degree;
  int tag = nd->tag;
  cilk_for(int i=0;i < degree;i++){
    if(nd->v[i]->color == color && (rand()%2) ){
      nd->color = -1;
      conflict = 1;
    }
  }
  return conflict;
}

int detect_all_conflictsx(boundary_table *bt){
  int size = bt->size;
  node** bnds = bt->nodes;
  int* conflicts = bt->conflicts;
  int count=0;
  srand(time(NULL));
	pthread_mutex_init(&m, NULL);

  cilk_for(int i=0; i < size;i++){
		pthread_mutex_lock(&m);
    if(conflicts[i]){
      int dc = detect_conflictsx(bnds[i]);
      count += dc;
      conflicts[i] = dc;
    }
		pthread_mutex_unlock(&m);
  }
  return count;
}
