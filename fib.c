#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
//- See more at: https://www.cilkplus.org/fibcpp#sthash.n5QxSvM9.dpuf

// Compile - g++ fib.c -fcilkplus
// Run - ./a.out

int fib(int n){
  if(n < 2)
    return n;
  int x = cilk_spawn fib(n-1);
  int y = fib(n-2);
  cilk_sync;
  return x + y;
}
int main(int argc, char *argv[]){
  int n = 39;
  if(argc > 1){
    if(atoi(argv[1]) < 1){
      printf("Usage: fib [workers]\n");
      return 1;
    }
  }
  clock_t start = clock();
  int result = fib(n);
  clock_t end = clock();

  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Fibonacci number #%d is %d.\n", n, result);
  printf("Calculated in %.3f seconds using %d workers.\n",
   duration, __cilkrts_get_nworkers());
  return 0;
}
