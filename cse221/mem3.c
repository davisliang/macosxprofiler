
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "rdtsc.h"


// Must run "sudo purge" each time before running this program for accurate results
int main() {
    // Open file, pre-filled with data
    int Fp = open("testFile.txt", O_RDWR);
    if (Fp < 0) {
        printf("Open failed\n");
        return -1;
    }
    
    // Get system page size
    unsigned int PAGE_SIZE = (int)((size_t) sysconf (_SC_PAGESIZE));
    fprintf(stderr, "%i\n", PAGE_SIZE);

    // Determine size of file to map
    unsigned int FILE_SIZE = 50000 * PAGE_SIZE;

    char* mem =(char*) mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, Fp, 0);

    char temp;
    uint64_t begin;
    uint64_t end;
    int i;
    int Leap = 40; // make leap big enough to avoid spatial locality

    begin = rdtsc();
    for (i = 0; i < 1000; i++)
    {
        // access the mapped memory by 40-page leaps to ensure page faulting   
        temp = mem[((i+1) * Leap * PAGE_SIZE)]; 
    }
    end = rdtsc();
    
    double cycleAvg = (double)(end - begin) / 1000;
    printf("Page Fault Cycle Average: %lf\n", cycleAvg);
    
    munmap(mem, FILE_SIZE);
    close(Fp);
    return 0;
}