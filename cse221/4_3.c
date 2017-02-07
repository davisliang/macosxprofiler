#include <stdio.h>
#include "rdtsc.h"
#include <time.h>


int main() {
  int iter = 1000000;
  double clock = 0;
  double start, end;
  int i = 0;

  
  for(i=0;i<iter;i++){
    time_t t;
    start = rdtsc();
    time(&t);
    end = rdtsc();

    clock += end - start;
  }

  printf("running %d time syscalls took %f time\n", iter, clock);
  return 0;
}
