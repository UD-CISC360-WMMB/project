#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

// ex: everything is built first, chassis and frame is placed first, then wheels and engine, then steering wheels
// print the car has been built

void make(char* str){
  int i=0;
  for(i=0;i<1000000;i++)
    printf("");
  printf("%s has/have been created.\n",str);
}

void place(char* str){
  int i=0;
  for(i=0;i<1000000;i++)
    printf("");
  printf("%s has/have been placed.\n",str);
}

// ordering threads to retain code structure
int main(){

  // spawn threads here
  cilk_spawn make("chassis");
  cilk_spawn make("frame");
  cilk_spawn make("wheels");
  cilk_spawn make("engine");
  cilk_spawn make("steering wheels");
  // making, ordering doesn't matter
  cilk_sync; // do placing after making

  // place chassis and frame, and sync
  cilk_spawn place("chassis");
  cilk_spawn place("frame");
  cilk_sync;

  // place wheels, engine then sync
  cilk_spawn place("wheels");
  cilk_spawn place("engine");
  cilk_sync;

  // place wheels, then sync
  cilk_spawn place("steering wheels");
  cilk_sync;

  // finished
  printf("The car has been built.\n");

}
