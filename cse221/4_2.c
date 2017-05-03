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
  int iter = 1;
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


