#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void) {
	int numb;
	int guess;
	srand(1000);
	numb = rand() % 10;

	
    printf("I've thought of a number. Enter your guess.\n");

	do {
		printf("> ");
        scanf("%d", &guess);
		if ( guess > numb ) {
			printf("Lower\n");
		}
		else if ( guess < numb ) {
			printf("Higher\n");
	    } 
	} while (guess != numb);
	printf("Well done, the number I thought of was %d.\n", numb);
	return 0;
}