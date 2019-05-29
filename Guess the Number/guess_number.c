#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int chosen, guess, i, j;

    srand(time(NULL));
    chosen = rand() % 10;

    printf("Guess a number between 1 and 9: ");
    scanf("%d", &guess);
    
    while (guess != chosen) {
        if (guess < chosen) {
            printf("Wrong. Go higher: ");
        }
        if (guess > chosen) {
            printf("Wrong. Go lower: ");
        }
        scanf("%d", &guess);
    }
    if (guess == chosen) {
        printf("Correct! The number was %d.\n", chosen);
    }
    
}