#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Starter: Incorrect usage retry with: ./Starter {Argument}\n");   // Program was ran incorrectly
        return -1;
    }
    char str[16];
    int pipe_1[2];

    if (pipe(pipe_1) < 0) { // Make pipe_1 into a pipe, if this fails, print that it failed, exit the program, and return -1
        printf("Starter[%d]: Pipe Failed",getpid());
        return -1;
    }

    sprintf(str,"%d", pipe_1[1]);  // Put the write end of the pipe into str so I can pass that to CharacterReader
    pid_t cpid = fork();
    if (cpid < 0) {
        printf("Starter[%d]: Fork Failed",getpid()); // If for fails, print that it failed and return -1
        return -1;
    }
    if (cpid == 0) { // Child
        execlp("./CharacterReader","CharacterReader",argv[1],str,NULL); // Replace child with the CharacterReader program
    } else { // Parent
        wait(NULL); // Wait for the child to finish (Kill the child when it finishes to not have a zombie)
        close(pipe_1[1]);   // Close write end of the pipe
        char number[10];
        read(pipe_1[0],number,10);  // Read content out of the pipe and store it in number
        close(pipe_1[0]);   // Close read end of the pipe
        printf("Starter[%d]: contents read from the read end pipe: %s\n",cpid,number);
        char SHM_Fibb[] = "SHM_Fibb1";
        char SHM_Prime[] = "SHM_Prime1";
        char SHM_Total[] = "SHM_Total1"; // Declaration of shared memory names
        
        int shmFibb = shm_open(SHM_Fibb, O_CREAT | O_RDWR, 0666);
        int shmPrime = shm_open(SHM_Prime, O_CREAT | O_RDWR, 0666);
        int shmTotal = shm_open(SHM_Total, O_CREAT | O_RDWR, 0666); // Create all shared memories, with read write perms and a create flag, mode was given to us

        if (shmFibb < 0 || shmPrime < 0 || shmTotal < 0) {
            printf("Starter[%d]: Shared memory failed to work. Error: %s\n",getpid(), strerror(errno));  // If shared memory creation failed for any of them, print so and return -1
            return -1;
        }

        ftruncate(shmFibb, 32);
        ftruncate(shmPrime, 32);
        ftruncate(shmTotal, 32);    // Make all shared memory size 32 bytes

        printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n",cpid,SHM_Fibb,shmFibb);
        printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n",cpid,SHM_Prime,shmPrime);
        printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n",cpid,SHM_Total,shmTotal);

        for (int i = 0; i < 3; i++) {   // Make 3 child processes and replace them with the respective program
            pid_t pid = fork();
            if (pid == 0) { //Child
                if (i == 0) {
                    execlp("./Fibb","Fibb",number,SHM_Fibb,NULL);
                } else if (i == 1) {
                    execlp("./Prime","Prime",number,SHM_Prime,NULL);
                } else if (i == 2) {
                    execlp("./Total","Total",number,SHM_Total,NULL);
                }
            }
        }
        for (int i = 0; i < 3; i++) {   // Wait in a separate for loop so each child runs concurrently
            wait(NULL);
        }

        int *fibbVal = mmap(0, 32, PROT_READ, MAP_SHARED, shmFibb, 0);
        int *primeVal = mmap(0, 32, PROT_READ, MAP_SHARED, shmPrime, 0);
        int *totalVal = mmap(0, 32, PROT_READ, MAP_SHARED, shmTotal, 0);    // Get pointers to each start of the shared memory

        int fibbValueRet = *fibbVal;
        int primeValueRet = *primeVal;
        int totalValueRet = *totalVal;  // Extract the value in shared memory (don't have to do this but if the child process 
                                        // produced more I would have to) into a local variable

        pid_t mypid = getpid();
        printf("Starter[%d] : Fibb last number:  %d\n",mypid,fibbValueRet);
        printf("Starter[%d] : Prime last number:  %d\n",mypid,primeValueRet);
        printf("Starter[%d] : Total last number:  %d\n",mypid,totalValueRet);

        int unFibb = shm_unlink(SHM_Fibb);
        int unPrime = shm_unlink(SHM_Prime);
        int unTotal = shm_unlink(SHM_Total); // Unlink all shared memories 
        if (unFibb < 0 || unPrime < 0 || unTotal < 0) {
            printf("Starter[%d]: Shared memory failed to unlink. Error: %s\n",getpid(), strerror(errno));  // If shared memory creation failed for any of them, print so and return -1
            return -1;
        }
    }
    return 1; // Return 1 to indicate success
}