#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "rdtsc.h"

int filesize = 32*1024*1024; //32 MB files
int PAGE = 4096;
int contention = 4;
char* files[4] = {"1","2","3","4"};

void seq(int currfile){
  void *page_buffer = malloc(4096);
  int file = open(files[currfile], O_RDONLY);
  fcntl(file, F_NOCACHE, 1);
  int num = filesize/PAGE;

  long start, end, total = 0;
  for(int i=0 ; i<num ; i++){
    //experiment start
    start = rdtsc();
    read(file, page_buffer, PAGE);
    end=rdtsc();
    //experiment end
    total += end-start;
  }
  close(file);
  printf("Latency: %ld\n", total/num); 
}

void ran(int currfile){
  void *page_buffer = malloc(PAGE);
  int file = open(files[currfile], O_RDONLY);
  fcntl(file, F_NOCACHE, 1);
  int num = filesize / PAGE;

  long start, end, total = 0;
  for (int i = 0; i < num; i++) {
    int randval = rand() % num;

    //experiment start
    start = rdtsc();
    lseek(file, randval*PAGE, SEEK_SET); // offset
    read(file, page_buffer, PAGE);
    end = rdtsc();
    //experiment end

    total += end - start;
  }

  close(file);
  printf("%ld\n", total/num); // output 21 bits after point

}

int main(int argc, char const *argv[])
{
  srand(time(NULL));
  for (int i = 0; i < contention; ++i) 
    if (fork()==0){ seq(i); exit(0); }

  return 0;
}

