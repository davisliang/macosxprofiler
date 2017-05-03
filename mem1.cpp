#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <mach/mach_time.h>
#include "rdtsc.h"
#include <math.h>

#define ITERATIONS 10000000
void measure_access_time(int arraysize, int arraystride)
{

  //declare the array with desired array size. all values are -1 by default.
  int* arr = (int*) malloc(sizeof(int) * arraysize);
  for (int i = 0;  i < arraysize; i++)
    arr[i] = -1;

  int pos = 0;
  //set values to array according to stride. 
  for(int i = arraystride; i < arraysize; i += arraystride)
  {
    arr[pos] = i;
    pos = i;
  }
  arr[pos] = 0;
  arr[arraysize - 1] = 0;

  //calculate the ram access time to read the array into caches and memory
  double sum = 0.0;
  int access = 0;
  srand(time(NULL));
  int c = rand()%arraysize; 

  float start = 0; float end = 0; float total = 0;
  float overhead = 0;
  start = rdtsc();
  for(int i = 0; i < ITERATIONS; i++)
  {
    c = access;
  }
  end = rdtsc();
  overhead = end - start;
  

  start = 0; end = 0; total = 0;
  start = rdtsc();
  for(int i = 0; i < ITERATIONS; i++)
  {
  	// TIMING THIS
    access = arr[c];
	c=access;
    // TIMING THIS
  }
  end = rdtsc();
  total = end - start;


  printf("\narraysize: %i \ntime: %f \n",arraysize/4, total-overhead) ; 
  
}



int main(int argc, const char* argv[])
{

  int minsize = (int) pow(2,10);
  long long int maxsize = (long long int) pow(2,30);
  int stridesize;

  stridesize = (int) pow(2,20); 
  for(long long int memsize = minsize; memsize <= maxsize; memsize = memsize*1.3 )
  {
    int testing_size = memsize / 4;
    measure_access_time(testing_size, stridesize);
  }
  
}