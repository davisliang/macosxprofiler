#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <mach/mach_time.h>
#include "rdtsc.h"
#include <math.h>

void experiment(int sizeInFourBytes, int stride) {
  //create array to nextItem memory from.
  //large arrays will overflow cache and cause misses.
  int* arr = (int*) malloc(sizeof(int) * sizeInFourBytes);
  int currIndex = 0;
  for(int i=0; i<sizeInFourBytes; i+=stride)
  {
    arr[currIndex] = i;
    currIndex = i;
  }
  arr[currIndex] = 0; arr[sizeInFourBytes-1]=0;
  // grab random item and start accessing to compute overhead
  srand(time(NULL));
  int c = rand()%sizeInFourBytes; 
  float start = 0; float end = 0; float total = 0;
  int nextItem = 0; float overhead = 0;
  start = rdtsc();
  for(int i = 0; i < 10000000; i++)
    c = nextItem;
  end = rdtsc();
  overhead = end - start;
  //run actual experiment
  start = 0; end = 0; total = 0;
  start = rdtsc();
  for(int i = 0; i < 10000000; i++)
  {
  	// TIMING THIS
    nextItem = arr[c]; c=nextItem;
    // TIMING THIS
  }
  end = rdtsc();
  total = end - start;
  printf("%i,%f\n",sizeInFourBytes*4, (float)((float)total-(float)overhead)/100000); 
}

int main(int argc, const char* argv[]) {
	float rate = 1.3; //rate of increase of memory
	float lowerbound = (float) 1024; //4kb
	float upperbound = (float) 1073741824;
	// STRIDE SIZE
	//int stridesize = (int) 1024; //4kb
	//int stridesize = (int) 4*1024; //16 kb
	//int stridesize = (int) 1024*1024/4; //1 MB
	int stridesize = (int) 512/4; //512 bytes 

	for(float arrsize = lowerbound; arrsize <= upperbound;)
	{
		arrsize *= rate;
		float testing_size = arrsize / 4;
		experiment((unsigned int)testing_size, (unsigned int)stridesize);
	}
}