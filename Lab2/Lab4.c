#include <stdio.h>

int factor(int n){
    int v0 = 1;
    int v1;
    for (int i = 2; i <= n ; i++)
    {
        for (int j = 1; j < i; j++)
        {
            v1 += v0;   // v1 = (i-1)! * i
        }  
        v0 = v1;    //v0 = i!
    }
    return v0;
}
int main(int argc, char const *argv[])
{
    int a = factor(5);
    printf("num is: %d", a);
    return 0;
}
