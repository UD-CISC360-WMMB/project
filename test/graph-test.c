#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/graph.h"

int main(int argc, char *argv[]){
	graph* g;
  p_graph pg;
	int size = atoi(argv[1]);
	int connections = atoi(argv[2]);
  
	g = rand_graph(size, connections);
  

  //pg = block_partition(g,20);
  pg = bfs_partition(g,5);
  
  label_boundary_nodes(&pg);
  collect_boundary_nodes(&pg);
  
  boundary_table *bt = pg.boundary_table;

  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  detect_all_conflicts(pg.boundary_table);
  printf("There are %d conflicts currently.\n",count_conflicts(pg.boundary_table));
  
    //   print_subgraphs(pg);


    // validate_color(g);
  
  /*
  sequential_color(g);
  printf("There are %d boundary nodes in this graph.\n They are: ",pg.num_bnds);
  validate_color(g);

  
  for(int i=0;i < pg.num_bnds;i++)
    printf(" %d", pg.bnds[i].node->tag);
  printf("\n");
  */

  
	return 0;
}
