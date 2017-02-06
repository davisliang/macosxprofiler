#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const int NUMBER_OF_THREADS = 10000;

void * thread_talk(void * thread_nr)
{
  cout << "a";
  pthread_exit(NULL);         //exit from current thread
}

void CreateThread(int i)
{
    pthread_t* first;

    pthread_create(first, NULL, thread_talk, static_cast<void*>(&i));

    pthread_join(*first, NULL);
}

int main(){
  
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        CreateThread(i);
    }

    return 0;
}