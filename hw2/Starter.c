#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Starter: Incorrect usage retry with: ./Starter {Argument}\n");   // Program was ran incorrectly
        return -1;
    }
    FILE* in = fopen(argv[1],"r");  // Open file given in argv[1] with read only permission
    char val[4];
    if (!in) {
        printf("Starter: File doesn't exist.\n");    // Failed to open the file print so and close
        return -1;
    }
    int Fibb;
    int Prime;
    int Count;
    while (fgets(val, 4, in)) {
        for (int i = 0; i < 3; i++) {   // Loop through 3 times for the 3 other executables to save writing a little code
            pid_t cpid = fork(); // Child's PID
            if (cpid < 0) {
                printf("Starter: Fork Failed");
                return -1;
            }
            if (cpid == 0) {
                if (i == 0) {
                    execlp("./Fibb","Fibb",val,NULL);   // Decide which program to execute based on what iteration the for loop is
                } else if (i == 1) {
                    execlp("./Prime","Prime",val,NULL);
                } else if (i == 2) {
                    execlp("./Total","Total",val,NULL);
                }
            } else {
                pid_t mpid = getpid(); // Get my PID of the parent
                int status;
                int exitStatus;
                printf("Starter[%d] : Forked process with ID %d.\n",mpid,cpid);
                printf("Starter[%d]: Waiting for process [%d].\n",mpid,cpid);
                wait(&status);  //Wait for the process to complete then store the status in status above using a pointer
                exitStatus = WEXITSTATUS(status); // Get the value returned from the process 
                printf("Starter: Child process %d returned %d.\n",cpid,exitStatus);
                if (i == 0) {
                    Fibb = exitStatus;  // Store the exit status of each program based on what iteration the for loop is
                } else if (i == 1) {
                    Prime = exitStatus;
                } else if (i == 2) {
                    Count = exitStatus;
                }
            }
        }
    }
    printf("fibb:  %d\n",Fibb);
    printf("Prime: %d\n",Prime);
    printf("total Count:       %d\n\n",Count);
    fclose(in);
    return 0;
}