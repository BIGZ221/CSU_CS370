#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int totalNum(int n) {
    int total = 0;
    for (int i = 0; i <= n; i++) {
        total += i;
    }
    return total;
}

int main(int argc, const char* argv[]) {
    int val = atoi(argv[1]);
    int total = totalNum(val);// Convert the string value into integer
    printf("Total[%d] : Sum = %d\n",getpid(),total);
    return total;
}