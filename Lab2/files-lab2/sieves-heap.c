#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 6
int antalNums = 0;
int count = 0;

void print_number(int n) {

    printf("%10d", n);
    antalNums++;
    if (antalNums % COLUMNS == 0){
        printf("\n");
    }
}

void print_sieves(int input) {
    
    //char primes[input + 1];
    char *primes = (char*) malloc(sizeof(char)*input + 1);
    for (int i = 0; i <= input; i++) {
        primes[i] = 1; // Initially mark all numbers as prime
    }

    // Apply the Sieve of Eratosthenes algorithm
    for (int j = 2; j * j <= input; j++) {
        if (primes[j]) {
            // If j is prime, mark all multiples of j as 0
            for (int i = j * j; i <= input; i += j) {
                primes[i] = 0;
            }
        }
    }

    // Print prime numbers
    for (int i = 2; i <= input; i++) {
        if (primes[i]) {
            print_number(i);
        }
    }
    /*suprise assignment*/
    int diff;
    int prevP = 2;
    for (int k = 3; k <= input; k++)
    {
        if (primes[k])
        {
            diff = k - prevP;
            if (diff == 4)
            {
                count++;
            }
            prevP = k;
        }        
    }
    
    free(primes);
}

int main(int argc, char *argv[]){
    // if(argc == 2)
    //     print_sieves(atoi(argv[1]));
    // else
    //     printf("Please state an interger number.\n");
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Prime numbers from 2 to %d are:\n", num);
    //time_t start = time(NULL);
    print_sieves(num);
    //time_t end = time(NULL);
    //printf("\nused time for print all prime number upp to %d is: %d\n", num, difftime(end, start));
    printf("\nnumber of distances 4: %d", count);
    return 0; 
}