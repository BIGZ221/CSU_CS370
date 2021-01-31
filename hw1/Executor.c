#include "Executor.h"

int get_iteration_no(int rand) {
    return rand % 50 + 50; //Returns a pseudorandom number between [50-99]
}

int get_arr_size(int rand) {
    return rand % 50 + 100; //Returns a pesudorandom number between [100-149]
}

char get_arr_val(int rand) {
    return rand % 26 + 65; //Returns a pseudorandom number betweeen [65-90]
}

float ratio(char *arr, int size, int *maxCountPointer) {
    float cVowel = 0;                       //cVowel and cConsonant are floats because if they are
    float cConsonant = 0;                   //ints they complete integer division resulting in a
    for (int i = 0; i < size; i++) {        //return value of 0 instead of the correction ratio
        char currChar = *(arr + i);
        if (currChar == 'A' || currChar == 'E' || currChar == 'I' || currChar == 'O' || currChar == 'U') {
            cVowel++;
        } else {
            cConsonant++;
        }
    }
    if (cVowel > *maxCountPointer) {
        *maxCountPointer = cVowel;  //Comparison if current Vowel counter is greater than previous max
    }
    return cVowel / cConsonant;
}

double get_running_ratio() {
    int maxCount = 0;
    int maxIteration = 0;
    float cRatio = 0.0;
    int iterations = get_iteration_no(rand());
    char *arr;
    
    for (int i = 0; i < iterations; i++) {
        int arrSize = get_arr_size(rand());
        arr = malloc(arrSize * sizeof(char)); //Allocate an array of characters with size: arrSize on the Heap
        for (int j = 0; j < arrSize; j++) {
            *(arr + j) = get_arr_val(rand());
        }
        int tmpCount = maxCount;
        cRatio += ratio(arr, arrSize, &tmpCount);
        if (tmpCount > maxCount) {
            maxCount = tmpCount;
            maxIteration = i + 1; //Iterations begin at 1 not zero
        }
        // If line below is commented out a memory leak is generated because on the next iteration we allocate more.
        free(arr);
    }
    printf("[Executor]: Number of iterations is %d\n",iterations);
    printf("[Executor]: Iteration with maximum vowel count is %d\n", maxIteration);
    return (cRatio / iterations);
}
