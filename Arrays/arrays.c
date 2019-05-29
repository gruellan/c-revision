#include <stdio.h>
#define ARRAY_LENGTH 10

int main() {
    int array[ARRAY_LENGTH];
    int i, j;
    int smallest, smallest_pos, largest, largest_pos;

    printf("Make an array.\n");
    for (i=0; i<ARRAY_LENGTH; i++) {
        printf("Element %d: ", i);
        scanf("%d", &array[i]);
    }

    // Print whole array
    printf("This is your array: \n");
    for (int i=0; i<ARRAY_LENGTH; i++) {
        printf("%d\n", array[i]);
    }

    // Print smallest number in array
    smallest = array[0];
    largest = array[0];
    for (int i=0; i<ARRAY_LENGTH; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            smallest_pos = i;
        }
        else if (array[i] > largest) {
            largest = array[i];
            largest_pos = i;
        }

    }  

    printf("The smallest number is: %d at position: %d\n", smallest, smallest_pos); 
    printf("The largest number is: %d at position: %d\n", largest, largest_pos);  

    return 0;
}