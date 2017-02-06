#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const int NUMBER_OF_THREADS = 5;

void * thread_talk(void * thread_nr)
{
  cout << "a";
  pthread_exit(NULL);         //exit from current thread
}

int main(){
  pthread_t thread[NUMBER_OF_THREADS];
  cout << "Starting all threads..." << endl;
  int temp_arg[NUMBER_OF_THREADS] ;
  /*creating all threads*/
  for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++){
    temp_arg[current_t]   = current_t;
    int result = pthread_create(&thread[current_t], NULL, thread_talk, static_cast<void*>(&temp_arg[current_t]))  ;
    if (result !=0){
      cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
    }
  }
  for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++){
    pthread_join(thread[current_t], NULL);
  }
  return 0;
}
