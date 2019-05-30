#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char spinReel(char options[]) {
    srand(time(NULL));
    int i = rand() % 4;
    char chosen = options[i];
    printf("%c", chosen);
    return chosen;
}

void printReels(char reels[]) {
    for (int i=0; i<3; i++) {
        printf("Reel %d: %c\n", i+1, reels[i]);
    }
}

int main() {
    int bell, orange, cherry, horseshoe;
    char b, o, c, h;
    char options[4] = {'b','o','c','h'};
    char reels[3];
    
    reels[0] = spinReel(options);
    reels[1] = spinReel(options);
    reels[2] = spinReel(options);

    printReels(reels);
}