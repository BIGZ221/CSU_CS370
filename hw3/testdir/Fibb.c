#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>

int fibonacci(int n) {
    int first = 0;
    int second = 1;
    int temp;
    int temp2;
    for (int i  = 0; i < n; i++) {
        printf("%d, ", first);
        temp2 = first; // Save the nth fibonaccii number for returning
        temp = first + second; // Second is old first + second but first is old second so we have to use a temp to save the new second
        first = second;
        second = temp;
    }
    return temp2;
}

int main(int argc, char* argv[]) {
    argc += 0;
    pid_t pid = getpid();   // Get my PID as the child
    int value = atoi(argv[1]);// Convert the string value into integer
    printf("%s[%d] : Number of terms in fibonacci series is %d\n",argv[0],pid,value);
    printf("%s[%d] : The first %d numbers of the Fibonacci sequence are:\n",argv[0],pid,value);
    int val = fibonacci(value);
    printf("\n");
    int shmFibb = shm_open(argv[2], O_RDWR, 0666);  // Open the shared memory from the name passed in as argv[2] with readwrite perms.

    int *fibbVal = mmap(0, 32, PROT_WRITE, MAP_SHARED, shmFibb, 0); // Give me a pointer to the shared memory where I am allowed to write

    *fibbVal = val; // Shared memory now contains val

    return val;
}