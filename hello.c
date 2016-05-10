#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

static void hello(){
//int i=0;
cilk_for(int i=0;i<1000000;i++)
printf("");
printf("Hello ");
}

static void world(){
//int i=0;
cilk_for(int i=0;i<1000000;i++)
printf("");
printf("world! ");
}

int main(){
    clock_t start = clock();
    cilk_spawn hello();
    cilk_spawn world();
    //cilk_spawn hello();
    //cilk_spawn world();
    //cilk_sync;
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Done in %.9f!\n", duration);
    printf("Currently using %d workers\n", __cilkrts_get_nworkers());

}
