#include "./graph.h"
#include "./data.h"
#include <stdio.h>
#include <stdlib.h>

subgraph** partition_graph(graph* g, int p_size){
  int g_size = g->size;
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
              if(pcounter%p_size==0){
                  col++;
              }
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
  subgraph** sub=malloc(g_size/p_size*sizeof(subgraph));
  int substep=0;
  for(int i=0;i<g_size;i+=p_size){
      node** nsg=malloc(p_size*sizeof(node*));
      int step=0;
      for(int j=i;j<i+p_size;j++){
          nsg[step]=nds[j];
          step++;
      }
      sub[substep]=new_subgraph(nsg,p_size);
      substep++;
  }
  return sub;
}
