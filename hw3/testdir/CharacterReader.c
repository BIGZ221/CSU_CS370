#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("CharacterReader[%d]: Incorrect arguments provided.\n",getpid());
	}
	int pipe_1 = atoi(argv[2]); // Convert pipe file descriptor into an int

	FILE* in = fopen(argv[1],"r");  // Open file given in argv[1] with read only permission

    if (!in) {
        printf("CharacterReader[%d]: File doesn't exist.\n",getpid());    // Failed to open the file print so and close
        return -1;
    }

	int sum = 0;
	char val[10];	// I chose 10 because of number 3 under "Starter does the following:" on page 2 of the pdf says array of size 10
	while (fgets(val, 10, in)) {	// While you can, read a max length of 10 characters from the file and add the int to sum;
		sum += atoi(val);
	}
	sprintf(val,"%d",sum); // Convert the int sum into a c-string and store that in val
	write(pipe_1, val,10); // Write val to the pipe with a max length of 10

	return 0;
}
