#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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
    pid_t pid = getpid();   // Get my PID as the child
    int value = atoi(argv[1]);// Convert the string value into integer
    printf("%s[%d] : Number of terms in fibonacci series is %d\n",argv[0],pid,value);
    printf("%s[%d] : The first %d numbers of the Fibonacci sequence are:\n",argv[0],pid,value);
    int val = fibonacci(value);
    printf("\n");
    return val;
}