#include <unistd.h>
#include <stdio.h>
#include "rdtsc.h"

	
int fd[2];

int main(){
	pipe(fd);
	pid_t childpid = fork();
	/*
	if(childpid == -1) {
		perror("GG fork got rekt.");
		return -1;
	}*/

	if(childpid == 0) {
		double begin, end;
		//have to read in the time from parent...
		//cannot use global begin here (we can use it for kernel thread though)
		read(fd[0], &begin, sizeof(begin));
		end = rdtsc();

		printf("a single fork context switch cost %f\n", end-begin);
		close(fd[0]);
		close(fd[1]);
		return 0;
	} else {
		double begin,end;	
		begin = rdtsc();
		//writing out time to child
		write(fd[1], &begin, sizeof(begin));

	}
}
