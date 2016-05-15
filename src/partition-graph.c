#include "./graph.h"
#include "./data.h"
#include <stdio.h>
#include <stdlib.h>



void label_boundary_nodes(p_graph *pg){
  int sub_size = pg->sub_size, num_subs = pg->num_subs;
  int num_bnds=0;
  node*** subs = pg->subs;
  for(int i=0; i < num_subs; i++){
    for(int j=0;j < sub_size; j++){
      node* nd = subs[i][j];
      node** v = nd->v;
      int degree = nd->degree;
      for(int k=0; k < degree; k++){
        if(v[k]->subgraph != i){
          if(nd->degree_out == 0)
            num_bnds++;
          nd->degree_out++;
        }
      }
    }
  }
  pg->boundary_table->size = num_bnds;
}



void collect_boundary_nodes(p_graph *pg){
  int sub_size   = pg->sub_size, num_subs = pg->num_subs;
  node*** subs   = pg->subs;

  boundary_table *bt = pg->boundary_table;
  int num_bnds = bt->size;
  
  node** bnds    = malloc(num_bnds*sizeof(node*));
  int* conflicts = malloc(num_bnds*sizeof(int));
  
  int b=0;
  for(int i=0; i < num_subs; i++){
    for(int j=0; j < sub_size; j++){
      node* nd = subs[i][j];
      if(nd->degree_out != 0){
        conflicts[b] = 1;
        bnds[b++] = nd;
      }
    }
  }
  bt->nodes = bnds;
  bt->conflicts = conflicts;
}


p_graph block_partition(graph* g, int sub_size){
  int g_size = g->size;
  int num_subs = g_size/sub_size + (g_size % sub_size != 0);
  node** v = g->v;
  node*** subs = malloc(num_subs * sizeof(node**));
  subs[0] = v + 0;
  
  int sub_index = 0, in_sub_index = 0;
  for(int i=0; i < g_size; i++){
    if(sub_size <= in_sub_index){
      in_sub_index = 0;
      sub_index++;
      subs[sub_index] = v + i;
    }
    g->v[i]->subgraph = sub_index;
    in_sub_index++;
  }

  p_graph pg;
  pg.sub_size = sub_size;
  pg.num_subs = num_subs;
  pg.subs = subs;
  pg.boundary_table = malloc(sizeof(boundary_table));
  return pg;
}



p_graph dfs_partition(graph* g, int p_size){
  int g_size = g->size;
  int num_p = g_size/p_size + (g_size%p_size != 0);
  int pcounter=1;
  int graphindexer=1;
  int more=1;
  node** nds=malloc(g_size*sizeof(node*));
  nds[0]=g->v[0];
  nds[0]->color=1;
  queue* Q=new_queue();
  enqueue(g->v[0],Q);
  int col=1;
  node* now;
  
  while(more==1){
    more=0;
     
     now=dequeue(Q);
     
      for(int k=0;k<now->degree;k++){
         
         node* i=now->v[k];
          if(i->color==0){
              col += !(pcounter%p_size);
              nds[pcounter]=i;
              i->color=col;
              pcounter++;
              enqueue(i,Q);
              more=1;
          }
      }
      if(Q->size==0&&graphindexer<g_size){
         enqueue(g->v[graphindexer],Q);
         more=1;
         if(g->v[graphindexer]->color==0){
              nds[pcounter]=g->v[graphindexer];
              nds[pcounter]->color=col;
              pcounter++;
         }
         graphindexer++;
      }
      if(Q->size!=0){
        more=1;
      }
  }
  node*** subs=malloc(num_p*sizeof(node**));
  int substep=0;
  for(int i=0;i<g_size;i+=p_size){
      node** nsg=malloc(p_size*sizeof(node*));
      int step=0;
      for(int j=i;j<i+p_size;j++){
          nsg[step]=nds[j];
          nds[j]->color = -1;
          nds[j]->subgraph = substep;
          step++;
      }
      subs[substep] = nsg;
      substep++;
  }

  p_graph pg;
  pg.sub_size = p_size;
  pg.num_subs = num_p;
  pg.subs = subs;
  pg.boundary_table = malloc(sizeof(boundary_table));
  return pg;
}
