/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int antalNums = 0;

void print_number(int n)
{
    printf("%10d", n);
    antalNums++;
    if (antalNums % COLUMNS == 0)
    {
        printf("\n");
    }
}

int is_prime(int n)
{
    // i <= sqrt (n)   ==   i * i <= n
    for (int i = 2; i * i <= n; i++)
    {
        // if remainder after modulo is 0, return 0
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void print_primes(int n)
{
    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that
    // the number of columns is stated in the define
    // COLUMNS
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i))
        {
            print_number(i);
        }
    }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    // if (argc == 2)
    //     print_primes(atoi(argv[1]));
    // else
    //     printf("Please state an interger number.\n");
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Prime numbers %d from 2 to are:\n", num);
    print_primes(num);
    return 0;
}