#include <stdio.h>
#include "rdtsc.h"

int main() {
  //initialize clock
  double clock = 0;
  int iter = 10000000;
  double begin, end;

  for(int i = 0; i<iter; i++){
    
    begin = rdtsc();
    end = rdtsc();

    clock += end-begin;
  }

  printf("%i clock starts took %f time \n", iter, clock);
  return 0;
}

