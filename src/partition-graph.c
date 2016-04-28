#include "./graph.h"
#include "./data.h"

subgraph** graph_partition(graph* g, int p_size){
  int g_size = g->size;
  int pcounter=1;
  node** nds=new node*[g_size];
  nds[0]=g->v[0];
  queue* Q=new_queue();
  enqueue(g->v[0],Q);
  int col=0;
  node* now=dequeue(Q);
  while(now!=null){
      for(node* i:now->v){
          if(i->color==0){
              if(pcounter%p_size==0){
                  col++;
              }
              nds[pcounter]=i;
              i->color=col;
              pcounter++;
              enqueue(i,Q)
          }
      }
      now=dequeue(Q);
  }
  subgraph** sub=new subgraph*[g_size/p_size];
  int substep=0;
  for(int i=0;i<g_size;i+=p_size){
      node** nsg=new node*[p_size];
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
