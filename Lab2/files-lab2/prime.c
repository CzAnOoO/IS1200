/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>

int is_prime(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        // om rest efter modulo är 0, return 0
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
    printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
    printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
