#include <iostream>
#include <thread>
using namespace std;

const int NUMBER_OF_THREADS = 10000;

void myfunc()
{
    cout << "a";
}

void CreateThread()
{
    thread first(myfunc);
    first.join();
}

int main()
{
    thread kthreads[NUMBER_OF_THREADS];

    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        kthreads[i] = thread(myfunc);
    }

    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        kthreads[i].join();
    }
}