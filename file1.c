#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "rdtsc.h"

char* filename = "f9_32";
int filesize = 1*1024*1024;
const off_t PAGE = 4096;
int main(int argc, const char * argv[])
{
    int eof = filesize-1;
    
    //read backwards
    int file = open(filename, O_RDONLY);
    lseek(file, eof, SEEK_SET);
    void* page_buffer = malloc(PAGE);
    int num = filesize/PAGE;

    for(int i = 0 ; i < num ; i++){
        lseek(file, PAGE*(-2), SEEK_CUR);
        read(file, page_buffer, PAGE);
    }
    
    //reopen and reset metrics
    close(file);
    file = open(filename, O_RDONLY);
    lseek(file, eof, SEEK_SET);
    
    // experiment start
    // read backwards (no prefetching)
    long start, end, total = 0;
    for(int i = 0 ; i < num ; i++){
        lseek(file, PAGE*(-2), SEEK_CUR);

        // start measuring time
        start = rdtsc();
        read(file, page_buffer, PAGE);
        end = rdtsc();
        // end measuring time

        total += end - start;
    }
    
    close(file);
    double result = total / (num);
    printf("Latency: %lf\n",result);
    return 0;
}

