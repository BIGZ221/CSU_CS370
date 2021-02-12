#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int primeNum(int n) {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < n; i++) { // There isn't an efficient way to compute primes and since the argument can't
        printf("%d, ", primes[i]);// be above 25 I put the first 25 primes here, then looped to print them out.
    }
    printf("\n");
    return primes[n-1]; // Return the nth prime which is index n-1
}

int main(int argc, const char* argv[]) {
    int val = atoi(argv[1]);    // Convert the string value into integer
    printf("Prime[%d]: First %d prime numbers are:\n",getpid(),val);
    return primeNum(val);
}