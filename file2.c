//Perform random and sequential file block read experiment

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "rdtsc.h"

int PAGE = 4*1024;
int filesize = 32*1024*1024;
char* filename = "f0_32";

double seq(void* buf)
{
    int fd = open(filename, O_RDONLY);
    int count = 0;
    int num = filesize / PAGE;
    fcntl(fd, F_NOCACHE, 1);

    long start, end, total;
    for(int i = 0 ; i < num ; i ++){
        start = rdtsc();
        read(fd, buf, PAGE); // return #byte when read successfully
        end = rdtsc();
        total += end - start;
    }

    close(fd);
    return total/num;
}

double ran(void* buf)
{
    int fd = open(filename, O_RDONLY); //open synchronously
    int num = filesize / PAGE;
    fcntl(fd, F_NOCACHE, 1);

    long start, end, total = 0;
    for (int i = 0; i < num; i++) {
        int randval = rand() % num;

        //begin experiment
        start = rdtsc();
        lseek(fd, randval * PAGE, SEEK_SET); 
        read(fd, buf, PAGE);
        end = rdtsc();
        //end experiment

        total += end - start;
    }
    close(fd);
    return total/num;
}

int main(int argc, const char *argv[]) //input the filesize and name of file
{
    srand(time(NULL)); // seed with time
    void* buf = malloc(PAGE);
    double sequential = seq(buf);
    double random = ran(buf);
    printf("Latency: %lf %lf\n", sequential, random); // output 21 bits after point
    return 0;
}