#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cilk/cilk.h>
// #include <pthread.h>
#include "../cilk/conflicts.h"
#include "../src/graph.h"


int print_colors(p_graph pg){
	int count = 0;
	for(int i = 0; i < pg.num_subs; i++){
		for(int j = 0; j < pg.sub_size; j++){
			node* nd = pg.subs[i][j];
			if(nd->color > -1){
				count++;
			}
		}
	}
	return count;
}



int main(int argc, char *argv[]){
	graph* g;
  p_graph pg;
	clock_t start, end;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);

	g = rand_graph(size, connections);


  //pg = block_partition(g,5);
  pg = bfs_partition(g,5);

  label_boundary_nodes(&pg);
  collect_boundary_nodes(&pg);
	start = clock();
  boundary_table *bt = pg.boundary_table;

  for(int x=0;x < 20; x++){
		start = clock();
    cilk_for(int i=0;i<pg.num_subs;i++){
      color_subgraph(pg,i);
		}

		int c = detect_all_conflicts(pg.boundary_table);
		int count = print_colors(pg);
		// int count = count_colors(pg);
    printf("There are %d conflicts currently. ",c);
		printf("Current colors: %d\n", count);
  }
	end = clock();
	double clocks = (end - start);
	printf("Took %.3f clocks.\n", clocks);




  /*
  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  print_subgraphs(pg);
  printf("\n\n\n");

  int c=detect_all_conflicts(pg.boundary_table);
  printf("There are %d conflicts currently.\n",c);

  print_subgraphs(pg);
  printf("\n\n\n");

  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  print_subgraphs(pg);
    // validate_color(g);


  //sequential_color(g);
  printf("There are %d boundary nodes in this graph.\n They are: ",pg.boundary_table->size);
  //validate_color(g);


  for(int i=0;i < pg.boundary_table->size;i++)
    printf(" %d", pg.boundary_table->nodes[i]->tag);
  printf("\n");

  */

	return 0;
}
