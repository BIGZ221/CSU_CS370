#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>

int primeNum(int n) {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < n; i++) { // There isn't an efficient way to compute primes and since the argument can't
        printf("%d, ", primes[i]);// be above 25 I put the first 25 primes here, then looped to print them out.
    }
    printf("\n");
    return primes[n-1]; // Return the nth prime which is index n-1
}

int main(int argc, const char* argv[]) {
    argc += 0;
    int val = atoi(argv[1]);    // Convert the string value into integer
    printf("Prime[%d]: First %d prime numbers are:\n",getpid(),val);
    int temp = primeNum(val);
    int shmPrime = shm_open(argv[2],O_RDWR, 0666); // Open the shared memory from the name passed in as argv[2] with readwrite perms.
    int *primeVal = mmap(0, 32, PROT_WRITE, MAP_SHARED, shmPrime, 0); // Give me a pointer to the shared memory where I am allowed to write

    *primeVal = temp; // Shared memory now contains temp (the last value in returned from primeNum)

    return temp;
}