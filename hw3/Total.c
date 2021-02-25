#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>

int totalNum(int n) {
    int total = 0;
    for (int i = 0; i <= n; i++) {
        total += i;
    }
    return total;
}

int main(int argc, const char* argv[]) {
    argc += 0;
    int val = atoi(argv[1]);
    int total = totalNum(val);// Convert the string value into integer
    printf("Total[%d] : Sum = %d\n",getpid(),total);
    int shmTotal = shm_open(argv[2], O_RDWR, 0666); // Open the shared memory from the name passed in as argv[2] with readwrite perms.
    int *totalVal = mmap(0, 32, PROT_WRITE, MAP_SHARED, shmTotal, 0); // Give me a pointer to the shared memory where I am allowed to write

    *totalVal = total; // Shared memory now contains total

    return total;
}