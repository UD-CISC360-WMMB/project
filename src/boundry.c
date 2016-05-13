#include "./graph.h"
#include "./data.h"
#include <stdio.h>
#include <stdlib.h>

void boundry(subgraph* sub){
  int s_size=sub->size;
  node** nds=sub->v;
  int nodeslist[s_size];
  int i,j,k;
  for (i=0;i<s_size;i++){
    nodeslist[i]=nds[i]->tag;
  }
  for (i=0;i<s_size;i++){
  int isboundry=0;
    for(j=0;j<nds[i]->degree;j++){
      int inlist=0;
      for(k=0;k<s_size;k++){
        if(nds[i]->v[j]->tag==nodeslist[k]){
          inlist=1;
        }
      }
      if(inlist!=1){
        isbondry=1;
      }
    }
    nds[i]->boundry=isboundry;
  }
