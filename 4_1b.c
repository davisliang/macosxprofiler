#include <stdio.h>
#include "rdtsc.h"

int main() {
  int iter = 100000000;
  double clock = 0;
  double start, end;
  int i = 0;

  start = rdtsc();
  for(i=0;i<iter;i++){
  }
  end = rdtsc();

  printf("running a %i loops took %f time\n", iter, end-start);
  return 0;
}
