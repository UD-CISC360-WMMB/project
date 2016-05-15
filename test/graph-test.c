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
  
  //	print_graph(g);
  //  pg = block_partition(g,5);
    pg = dfs_partition(g,5);
  
  label_boundary_nodes(&pg);
  collect_boundary_nodes(&pg);
  
  boundary_table *bt = pg.boundary_table;
  
  
  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  printf("There are %d conflicts currently.\n",count_conflicts(bt));
    
  detect_all_conflicts(bt);
  printf("There are %d conflicts currently.\n",count_conflicts(bt));


  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  detect_all_conflicts(bt);
  printf("There are %d conflicts currently.\n",count_conflicts(bt));


  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  detect_all_conflicts(bt);
  printf("There are %d conflicts currently.\n",count_conflicts(bt));

  for(int i=0;i<pg.num_subs;i++)
    color_subgraph(pg,i);

  detect_all_conflicts(bt);
  printf("There are %d conflicts currently.\n",count_conflicts(bt));

  //  print_subgraphs(pg);


  //  validate_color(g);

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
