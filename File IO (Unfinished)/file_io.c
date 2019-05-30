#include <stdio.h>
#include <string.h>

// Need to implement Hacker Edition (Week 8)
int main(){
    int totalHits = 0;
    int mozillaHits = 0;
    int possibleAttacks = 0;

    //Open the file 'access.log' for reading
    FILE *handle;
    handle = fopen("access.log", "r");

    if (handle != NULL) {
        // Read each line of text from the file and print it
        char lineOfText[800];

        // Loop through each line of text in the file
        while (fgets(lineOfText, 800, handle) != NULL) {
            totalHits = totalHits + 1;

            // Check if using Mozilla
            if(strstr(lineOfText, "Mozilla") != NULL){
                mozillaHits++;
            }

            if (strncmp(lineOfText, "66.249.66", 9) == 0) {
                possibleAttacks++;
                printf("*ALERT: POSSIBLE ATTACK*\n %s\n", lineOfText);
            }
        }

        printf("Total number of hits: %d\n", totalHits);
        printf("Hits from Firefox browsers: %d\n", mozillaHits);
        printf("Number of possible attacks: %d\n", possibleAttacks);

        fclose(handle);
    }
}