#include <sys/time.h>
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rdtsc.h"
#include <math.h>

int main(int argc, char* argv[]) {
	int numMB = 100;
	int bytesPerLong=8;
	int totalBytes = numMB*pow(2,20); 
	int numLongs = totalBytes/bytesPerLong;
	long tmp;
	long *array = (long*) malloc (totalBytes);
	memset (array, -1, totalBytes); //set size bytes
	long *p = array;
	long *end = array + numLongs;
	float startOverhead=0;float endOverhead=0;float overhead = 0;
	float startOverheadtemp=0;float endOverheadtemp=0;
	startOverhead = rdtsc();
	startOverheadtemp = rdtsc();
	while(++p < end){
		tmp ^= 1;
	}
	endOverheadtemp = rdtsc();
	endOverhead = rdtsc();

	overhead = endOverhead - startOverhead;

	
	p = array;
	end = array + numLongs;
	double timerStart = 0 ; double timerEnd = 0; double total = 0;
	
	timerStart = rdtsc();
	while(++p < end){
		*p ^= tmp;
	}
	timerEnd = rdtsc();

	total = timerEnd - timerStart-overhead;
	printf ("time: %lf, read bandwidth = %lf MB/s\n", total, 2*numMB*2.7/((double)(total)/ 1e9));
	free (array);
	return (int) tmp;
}
