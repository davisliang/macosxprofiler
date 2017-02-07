#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "rdtsc.h"

void* thread_kill(void * thread_nr){
	pthread_exit(NULL);
}

int main() {
	int iter = 500;
	double clock = 0;
	double begin, end;
	int i = 0;

	
	for(i=0; i <iter ; i++) {
		pthread_t first;

		begin = rdtsc();
		pthread_create(&first, NULL, thread_kill, (void *)&i);
		pthread_join(first, NULL);
		end = rdtsc();

		clock += end-begin;
	}
	
	printf("ran %i iterations of pthread_create cost %f\n", iter, clock);


}