//Run the code with the '-lm' compiler flag, to allow sqrt to work
#include <stdio.h>
#include <cilk/cilk.h>
#include <sys/time.h>
#include <math.h>

int isPrime(int n){
int limit = sqrt(n);
int i = 0; for(i=2; i<=limit; i++)
if(n%i == 0)
return 0;
return 1;
}

int main(){

int x;
double seconds = 0.0;
int gs = 25000;
for(x = 0; x < 10; x++){

int n = 10000000;
// int gs = 25000; //grainsize
int numPrimes = 0;
//int i;
struct timeval start,end;

gettimeofday(&start,NULL); //Start timing the computation

#pragma grainsize = gs
cilk_for(int i = 0; i < n/gs; i++){
int j; for(j = i*gs+1; j < (i+1)*gs; j += 2){
if(isPrime(j))
numPrimes++;
}
}

gettimeofday(&end,NULL); //Stop timing the computation

double myTime = (end.tv_sec+(double)end.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000);

printf("Found %d primes in %lf seconds.\n",numPrimes,myTime);
seconds += myTime;
}
seconds /= 10;
printf("Average seconds... = %lf, grain size = %d\n", seconds, gs);
}
