#include <iostream>
using namespace std;

int arg0()
{
    return 0;
}

int arg1(int a)
{
    return 0;
}

int arg2(int a, int b)
{
    return 0;
}

int arg3(int a, int b, int c)
{
    return 0;
}

int arg4(int a, int b, int c, int d)
{
    return 0;
}

int arg5(int a, int b, int c, int d, int e)
{
    return 0;
}

int arg6(int a, int b, int c, int d, int e, int f)
{
    return 0;
}

int arg7(int a, int b, int c, int d, int e, int f, int g)
{
    return 0;
}

int main()
{
    for(int i = 0; i < 1000000000; i++)
    {
        //arg0();
        //arg1(1);
        //arg2(1, 1);
        //arg3(1, 1, 1);
        //arg4(1, 1, 1, 1);
        //arg5(1, 1, 1, 1, 1);
        //arg6(1, 1, 1, 1, 1, 1);
        arg7(1, 1, 1, 1, 1, 1, 1);
    }
}

