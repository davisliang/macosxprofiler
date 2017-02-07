Processor:

//rdtsc.h

#ifndef __RDTSC_H_DEFINED__
#define __RDTSC_H_DEFINED__


#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
 __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
 return x;
}
#elif defined(__x86_64__)

static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#elif defined(__powerpc__)

static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int result=0;
  unsigned long int upper, lower,tmp;
  __asm__ volatile(
    "0:      \n"
    "\tmftbu   %0   \n"
    "\tmftb    %1   \n"
    "\tmftbu   %2   \n"
    "\tcmpw    %2,%0    \n"
    "\tbne 0b     \n"
    : "=r"(upper),"=r"(lower),"=r"(tmp)
    );
  result = upper;
  result = result<<32;
  result = result|lower;

  return(result);
}

#else

#error "No tick counter is available!"

#endif


/*  $RCSfile:  $   $Author: kazutomo $
 *  $Revision: 1.6 $  $Date: 2005/04/13 18:49:58 $
 */

#endif


//4_1a.c
#include <stdio.h>
#include "rdtsc.h"

int main() {
  //initialize clock
  int clock = 0;
  int iter = 10000000;
  double begin, end;


  for(int i = 0; i<iter; i++){
    
    begin = rdtsc();
    end = rdtsc();

    clock += end-begin;
  }

  printf("%d clock starts took %d time \n", iter, clock);
  return 0;
}


/*
10000000 clock starts took 352371870 time 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
10000000 clock starts took 355151113 time 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
10000000 clock starts took 361513527 time 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
10000000 clock starts took 355170894 time 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
10000000 clock starts took 416354109 time 
*/

//4_1b.c
#include <stdio.h>
#include "rdtsc.h"

int main() {
  int iter = 100000000;
  double clock = 0;
  double start, end;
  int i = 0;

  start = rdtsc();
  for(i=0;i<iter;i++){
  }
  end = rdtsc();

  printf("running a %i loops took %f time\n", iter, end-start);
  return 0;
}

/*
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running a 100000000 loops took 668587661.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running a 100000000 loops took 658716739.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running a 100000000 loops took 657396557.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running a 100000000 loops took 668690753.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running a 100000000 loops took 667989429.000000 time
*/


//4_2.c
#include <stdio.h>
#include "rdtsc.h"

int func0(){return 0;}

int func1(int a){return 0;}

int func2(int a, int b){return 0;}

int func3(int a, int b, int c){return 0;}

int func4(int a, int b, int c, int d){return 0;}

int func5(int a, int b, int c, int d, int e){return 0;}

int func6(int a, int b, int c, int d, int e, int f){return 0;}

int func7(int a, int b, int c, int d, int e, int f, int g){return 0;}

int main() {
  int iter = 10000000;
  double begin, end;
  int i = 0;

  double clock = 0;
  for(i = 0; i < iter; i++){
    begin = rdtsc();
    func0();
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of zero arg requires %f time\n", iter, clock);

  
  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func1(1);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of one arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func2(1,2);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of two arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func3(1,2,3);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of three arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func4(1,2,3,4);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of four arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func5(1,2,3,4,5);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of five arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func6(1,2,3,4,5,6);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of six arg requires %f time\n", iter, clock);

  clock = 0;
  for(i = 0; i < iter; i ++){
    begin = rdtsc();
    func7(1,2,3,4,5,6,7);
    end = rdtsc();
    clock += end - begin;
  }
  printf("ran %i iterations of seven arg requires %f time\n", iter, clock);

}


/*
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 10000000 iterations of zero arg requires 333323814.000000 time
ran 10000000 iterations of one arg requires 347783718.000000 time
ran 10000000 iterations of two arg requires 307879647.000000 time
ran 10000000 iterations of three arg requires 286818273.000000 time
ran 10000000 iterations of four arg requires 289853607.000000 time
ran 10000000 iterations of five arg requires 320514777.000000 time
ran 10000000 iterations of six arg requires 299630010.000000 time
ran 10000000 iterations of seven arg requires 321414795.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 10000000 iterations of zero arg requires 302840337.000000 time
ran 10000000 iterations of one arg requires 313547424.000000 time
ran 10000000 iterations of two arg requires 295875681.000000 time
ran 10000000 iterations of three arg requires 472509868.000000 time
ran 10000000 iterations of four arg requires 285351240.000000 time
ran 10000000 iterations of five arg requires 326566974.000000 time
ran 10000000 iterations of six arg requires 295398216.000000 time
ran 10000000 iterations of seven arg requires 338210347.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 10000000 iterations of zero arg requires 367973358.000000 time
ran 10000000 iterations of one arg requires 340470194.000000 time
ran 10000000 iterations of two arg requires 296147851.000000 time
ran 10000000 iterations of three arg requires 317987350.000000 time
ran 10000000 iterations of four arg requires 306069033.000000 time
ran 10000000 iterations of five arg requires 324344360.000000 time
ran 10000000 iterations of six arg requires 334698125.000000 time
ran 10000000 iterations of seven arg requires 338067883.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 10000000 iterations of zero arg requires 291354485.000000 time
ran 10000000 iterations of one arg requires 338294083.000000 time
ran 10000000 iterations of two arg requires 316757679.000000 time
ran 10000000 iterations of three arg requires 279299628.000000 time
ran 10000000 iterations of four arg requires 290491583.000000 time
ran 10000000 iterations of five arg requires 319601355.000000 time
ran 10000000 iterations of six arg requires 281896113.000000 time
ran 10000000 iterations of seven arg requires 323304798.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 10000000 iterations of zero arg requires 312676292.000000 time
ran 10000000 iterations of one arg requires 314483258.000000 time
ran 10000000 iterations of two arg requires 313870803.000000 time
ran 10000000 iterations of three arg requires 321114312.000000 time
ran 10000000 iterations of four arg requires 327698752.000000 time
ran 10000000 iterations of five arg requires 330326973.000000 time
ran 10000000 iterations of six arg requires 348883602.000000 time
ran 10000000 iterations of seven arg requires 364268844.000000 time
*/


//4_3.c
#include <stdio.h>
#include "rdtsc.h"
#include <time.h>


int main() {
  int iter = 1000000;
  double clock = 0;
  double start, end;
  int i = 0;
  
  for(i=0;i<iter;i++){
    time_t t;
    start = rdtsc();
    time(&t);
    end = rdtsc();

    clock += end - start;
  }

  printf("running %d time syscalls took %f time\n", iter, clock);
  return 0;
}


/*
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running 1000000 time syscalls took 653719459.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running 1000000 time syscalls took 677506722.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running 1000000 time syscalls took 713940648.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running 1000000 time syscalls took 612547773.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
running 1000000 time syscalls took 668992572.000000 time
*/

//4_4.c
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

/*
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
500 runs of fork thread takes 704563628.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
500 runs of fork thread takes 704908464.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
500 runs of fork thread takes 764700675.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
500 runs of fork thread takes 702936242.000000 time
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
500 runs of fork thread takes 707193694.000000 time
*/




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

    if(userThreadPID == -1){
      printf("GG thread got rekt\n");
      return -1;
    }
    else if(userThreadPID == 0) {
      // in child thread. should return (or else extra logic)
      return 0;
    }else {
      // in parent thread
      clock += end - begin;
    }
  }

  printf("%i runs of fork thread takes %f time\n", iter, clock);
}
/*

see: bulk.fefe.de/scalable-networking.pdf 
page 29-32

Note: user threads seem much slower to make...

Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 500 iterations of pthread_create cost 36284167.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 500 iterations of pthread_create cost 38197415.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 500 iterations of pthread_create cost 37633229.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 500 iterations of pthread_create cost 38659440.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
ran 500 iterations of pthread_create cost 35383912.000000
*/


//4_5.c
#include <unistd.h>
#include <stdio.h>
#include "rdtsc.h"

  
int fd[2];

int main(){
  
  int iter = 5;

  int i = 0;

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


/*
Note: user threads seem much faster to switch between (no context switch)
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
a single fork context switch cost 1618434.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
a single fork context switch cost 1594680.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
a single fork context switch cost 1597248.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
a single fork context switch cost 1655535.000000
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
a single fork context switch cost 1813341.000000
*/

//4_5b.c
#include <stdio.h>
#include <pthread.h>
#include "rdtsc.h"
#include <unistd.h>

int fd[2];
double begin, end;

void* thread_pipe(void* thread_nr){
  
  read(fd[0], "", sizeof(""));
  end = rdtsc();
  printf("single context switch in kernel thread cost %f \n", end-begin);
  close(fd[0]);
  close(fd[1]);
  pthread_exit(NULL);
}

int main(){
  //int iter = 5;
  int i=0;

  pipe(fd);
  pthread_t first;
  pthread_create(&first, NULL, thread_pipe, (void*)&i);
  begin = rdtsc();
  write(fd[1],"",sizeof(""));
  pthread_exit(NULL);

}

/*
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
single context switch in kernel thread cost 248718.000000 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
single context switch in kernel thread cost 247044.000000 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
single context switch in kernel thread cost 260085.000000 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
single context switch in kernel thread cost 275250.000000 
Daviss-MacBook-Pro:cse221 Davis$ ./a.out 
single context switch in kernel thread cost 273873.000000 
*/


