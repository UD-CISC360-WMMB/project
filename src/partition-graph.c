#include "./graph.h"
#include "./data.h"
#include <stdio.h>
#include <stdlib.h>

subgraph** partition_graph(graph* g, int p_size){
  int g_size = g->size;
  int pcounter=1;
  int grapindexer=1;
  int more=1;
  node** nds=malloc(g_size*sizeof(node*));
  nds[0]=g->v[0];
  queue* Q=new_queue();
  enqueue(g->v[0],Q);
  int col=0;
  node* now;
  printf("%s\n","Test1");
  while(more==1){
    more=0;
     printf("%s\n","Test1a");
     now=dequeue(Q);
     printf("%s\n","Test1b");
      for(int k=0;k<now->degree;k++){
         printf("%s\n","Test1aa");
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
           printf("%s\n","Test1ab");
      }
      if(more==0&&graphindexer<g_size){
         enqueue(g->v[graphindexer],Q);
         graphindexer++;
      }
       printf("%s\n","Test1c");
  }
  printf("%s\n","Test2");
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
  printf("%s\n","Test3");
  return sub;
}
