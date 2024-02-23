#include <stdio.h>
int main(int argc, char const *argv[])  
{
    //int a = 7; 
    //int *p = &a;
    //*p + 1 = a + 1
    // p + 1 = &a + 1
    //la t1, p = *p
    // use t1 
    int * p; /* Declare p as pointer, so that p can hold an address. */
    char cs[ 9 ] = "Bonjour!";
    char * cp = cs; /* Declare cp as pointer, initialise cp to point to cs */
    int size_cp = sizeof(cp);
    printf("size of cp innan: %d\n", size_cp);
    p = (int*)cp;
    int size_cpA = sizeof(cp);
    printf("size of cp after: %d\n", size_cpA);
    return 0;
}