#include <stdio.h>

int main () {
   int length, i, j;
   printf("Enter length: ");
   scanf("%d", &length);

   for (i=0; i<length; i++) {
        for (j=0; j<length; j++) {
            // Check if the current row is the first or last
            if(i==0 || i==(length-1)){
               printf("*");
            }

            // Check if the current column is the first or last
            else if (j==0 || j==(length-1)) {
                printf("*");
            }
            else {
                printf(" ");
            }
       }
       // Print new line after each row
       printf("\n");   
   }
   return(0);
}