#include <stdio.h>

int main () {
   int length, i, j;
   printf("Enter length: ");
   scanf("%d", &length);

    for (i=0; i<length; i++) {
        for (j=length; j!=i; j--){
        printf("*"); 
        }    
        printf("\n");
    }

    // Print new line after each row
    return(0);
}