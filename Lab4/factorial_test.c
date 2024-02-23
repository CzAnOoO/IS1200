#include <stdio.h>

int factorial(int n){
    int v0 = 1;
    int v1;
    for (int i = 1; i < n ; i++)	// 1, 2, 3, .... n-1, n
    {
        for (int j = 0; j < i; j++)
        {
            v1 += v0;   // v1 = (i-1)! * i = i!
        }  
        v0 = v1;    //v0 = i!
    }
    return v0;
}

int main(int argc, char const *argv[])
{
    int n = 3;
    int a = factorial(n);
    printf("factorial of %d is: %d\n", n, a);
    return 0;
}
