#include <stdio.h>

#define COLUMNS 6
int antalNums = 0;

void print_number(int n) {

    printf("%10d", n);
    antalNums++;
    if (antalNums % COLUMNS == 0){
        printf("\n");
    }
}

void print_sieves(int input) {
    // use index as number, that is why array lenth be input + 1
    char primes[input + 1];
    for (int i = 0; i < input; i++) {
        primes[i] = 1; // Initially mark all numbers as prime
    }

    // Apply the Sieve of Eratosthenes algorithm
    for (int j = 2; j * j <= input; j++) {
        if (primes[j]) {
            // If j is not prime, mark all multiples of j as 0
            for (int i = j * j; i <= input; i += j) {
                primes[i] = 0;
            }
        }
    }

    // Print prime numbers
    for (int i = 2; i <= input; i++) {
        // i is index = number
        if (primes[i]) {
            print_number(i);
        }
    }
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
    print_sieves(num);
    return 0; 
}