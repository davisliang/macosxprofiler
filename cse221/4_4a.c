#include "rdtsc.h"
#include <stdio.h>
#include <unistd.h>


int main() {
	double clock = 0;
	double begin, end;
	int iter = 500;
	int i = 0;

	for(i = 0; i < iter; i ++){
		begin = rdtsc();
		pid_t userThreadPID = fork();
		end = rdtsc();

		
		/*comment out to minimize cost

		if(userThreadPID == -1){
			printf("GG thread got rekt\n");
			return -1;
		}
		else */

		if(userThreadPID == 0) 
			// in child thread. should return (or else extra logic)
			return 0;
		
		// in parent thread
		clock += end - begin;
		
	}

	printf("%i runs of fork thread takes %f time\n", iter, clock);
}