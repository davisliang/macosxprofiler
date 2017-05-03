#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "rdtsc.h"

int PAGE = 4*1024;
int filesize = 4*1024*1024;

double seq(char *file, void* buf) {
    int fd = open(file, O_RDONLY);
    fcntl(fd, F_NOCACHE, 1);
    int num = filesize/PAGE;

    long start, end, total = 0;
    for(int i = 0 ; i < num ; i++){

        //run experiment
        start = rdtsc();
        read(fd, buf, PAGE); 
        end = rdtsc();
        //run experiment

        total += end - start;
    }

    close(fd);
    return total/num;
}

double ran(char *file, void* buf) {
    int i = 0;
    int randval;
    int fd = open(file, O_SYNC); //open synchronously
    fcntl(fd, F_NOCACHE, 1);
    int num = filesize / PAGE;
   
    long start, end, total = 0;
    for (i = 0; i < num; i++) {
        randval = rand() % num;

        //start experiment
        start = rdtsc();
        lseek(fd, randval * PAGE, SEEK_SET);
        read(fd, buf, PAGE);
        end = rdtsc();
        //end experiment

        total += end - start;
    }
    close(fd);
    return total / num;
}

int main(int argc, const char *argv[]) {
    void *buf = malloc(PAGE);
    srand(time(NULL));
    double result = seq("/mnt/srv/home/datafile", buf);
    printf("Latency: %lf\n", result);     
    return 0;
}
