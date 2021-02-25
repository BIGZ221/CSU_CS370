Starter.c
    This is the main file ran by:
        ./Starter "filename"
    Starter will fork to CharacterReader which will compute the sum in "filename"
    then it will setup shared memory to use between Fibb, Prime, and Total. Closes
    all pipes, unlinks all shared memory, and wait's (kills) any child processes to 
    be good and clean up the program while it runs. If a fork fails or a file is 
    unable to be opened or a shared memory segment fails it will print an error and 
    return -1
    ** I am not sure why but when shared memory names are SHM_Fibb, SHM_Prime, SHM_Total
    the program will fail to open shared memory with error: Permission Denied but if you
    change the names to SHM_Fibb1, SHM_Prime1, SHM_Total1 it will work fine, originally
    the SHM_Fibb, SHM_Prime, SHM_Total names worked fine but now they do not even though
    I unlink the shared memory at the end of the program.
    Rewrote 95% from HW2
Fibb.c
    Prints the first n fibonacci numbers and returns the nth
    through shared memory can be ran by "./Fibb 4" where 4 is 
    any number you want was written using a for loop instead 
    of the recursive method. 
    Reused 90% from HW2
Prime.c
    Prints the first n prime numbers
    Only supports up to the 25th prime number
    can be ran by "./Prime 4" where 4 is any number between [1-25]
    Was implemented by googling the first 25 primes since there
    is not a true way to calculate prime numbers efficiently. Returns
    the last prime number through shared memory.
    Reused 90% from HW2
Total.c
    Prints the sum of the first n numbers
    can be ran by "./Total 4" where 4 is any number you want
    Was written using a for loop from 0-n and keeping a running Total.
    Returns the sum through shared memory.
    Reused 96% from HW2
CharacterReader.c
    Takes in a filename and pipe file descriptor for the write end of the pipe.
    Goes through the whole file summing every entry then when it completed writes
    the sum into the pipe for Starter to read. Does not close the Pipe, that is
    the job of Starter.
    Fresh new code
Additional Information:
    None have a good day.

Questions:
    1.Name the function that is used to create a pipe. Which ends denotes the read and the write ends of a pipe? (2 points)
        pipe(int fd[2]);
        fd[0] = Read end    fd[1] = Write end
    2.Name the function used to map files or devices in to memory? (1 point)
        shm_open() allows you to do this
    3.Name the function used to open a shared memory object? What does it return? (2 points)
        mmap allows you to open a shared memory object and it returns a pointer to the object, at a specified offset. 