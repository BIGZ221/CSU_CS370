#include "Executor.h"

int main(int argc,const char *argv[]) {
    argc = argc + 1 - 1; //Warning complained about not using argc anywhere
    int seed = atoi(argv[1]); //If an argument is not provided it will Seg Fault
    srand(seed);
    printf("[Starter]: With seed: %d\n", seed);
    double running_ratio = get_running_ratio();
    printf("[Starter]: Running ratio: %lf\n", running_ratio);
}
