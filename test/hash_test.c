#include <stdio.h>
#include "../src/hash.h"

int main( int argc, char **argv ) {
  hashtable *ht = ht_create(256);
  
  ht_set( ht, "apple", "green" );
  ht_set( ht, "banana", "yellow" );
  ht_set( ht, "apple", "yellow" );
  ht_set( ht, "orange", "orange" );
  ht_set( ht, "plum", "purple" );
  ht_set( ht, "apple", "red" );
  
  printf( "%s: %s\n","apple", ht_get( ht, "apple" ) );
  printf( "%s: %s\n","banana", ht_get( ht, "banana" ) );
  printf( "%s: %s\n","orange", ht_get( ht, "orange" ) );
  printf( "%s: %s\n","plum", ht_get( ht, "plum" ) );
  ht_delete(ht);
}
