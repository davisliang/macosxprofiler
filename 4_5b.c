#include <stdio.h>
#include <pthread.h>
#include "rdtsc.h"
#include <unistd.h>

int fd[2];
//double begin, end;
void* thread_pipe(void* thread_nr){
	double begin, end;
	read(fd[0], &begin, sizeof(begin));
	end = rdtsc();
	printf("single context switch in kernel thread cost %f \n", end-begin);
	close(fd[0]);
	close(fd[1]);
	pthread_exit(NULL);
}

int main(){
	//int iter = 5;
	int i=0;
	double begin, end;
	pipe(fd);
	pthread_t first;
	pthread_create(&first, NULL, thread_pipe, (void*)&i);
	begin = rdtsc();
	//write(fd[1],"",sizeof(""));
	write(fd[1],&begin,sizeof(begin));
	pthread_exit(NULL);

}

