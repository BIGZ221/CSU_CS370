Starter.c
    This is the main file ran by:
        ./Starter "filename"
    Starter will fork multiple times to call each of the other file
    executables and produce the correct output.
    If a fork fails or a file is unable to be opened it will print
    an error and return -1
Fibb.c
    Prints the first n fibonacci numbers and returns the nth
    can be ran by "./Fibb 4" where 4 is any number you want
    Was written using a for loop instead of the recursive method
Prime.c
    Prints the first n prime numbers
    Only supports up to the 25th prime number
    can be ran by "./Prime 4" where 4 is any number between [1-25]
    Was implemented by googling the first 25 primes since there
    is not a true way to calculate prime numbers efficiently
Total.c
    Prints the sum of the first n numbers
    can be ran by "./Total 4" where 4 is any number you want
    Was written using a for loop from 0-n and keeping a running Total

Additional Information:
    None have a good day.

Questions:
    1. 8 bits of the status
    2. #include <sys/wait.h>
    3. In a child process Fork() returns 0
    4. fork can fail if there are no more available process id's to take
    5. I am doing Sequential processing to ensure correct formatting of output
    6. With the max value of 25 the sum is 325 but that number does not fit in
        the 8 bits of WEXITSTATUS so it is returned as 69