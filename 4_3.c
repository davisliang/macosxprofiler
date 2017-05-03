//gcc -std=c90 4_3.c
#include <stdio.h>
#include "rdtsc.h"
#include <sys/time.h>
#include <sys/syscall.h>

int main() {
  int iter = 1000000;
  double clock = 0;
  double start, end;
  int i = 0;

  
  for(i=0;i<iter;i++){
    struct timeval tv;
    
    start = rdtsc();
    syscall(96);
    //sys_gettimeofday(&tv, NULL);
    end = rdtsc();

    clock += end - start;
  }

  printf("running %d time syscalls took %f time\n", iter, clock);
  return 0;
}
