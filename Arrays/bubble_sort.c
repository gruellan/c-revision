#include <stdio.h> 
  
void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubbleSort(int arr[], int n) { 
   int i, j; 
   for (i = 0; i < n-1; i++)       
    
       for (j = 0; j < (n-i-1); j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 
  
void printArray(int arr[], int size) { 
    printf("Sorted array: \n"); 
    for (int i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
int main() { 
    int arr[7];// A function to implement bubble sort 
    printf("Make an array.\n");
    for (int i=0; i<7; i++) {
        printf("Element %d: ", i);
        scanf("%d", &arr[i]);
    }
    int n = sizeof(arr)/sizeof(arr[0]); 
    bubbleSort(arr, n); 
    printArray(arr, n); 
    return 0; 
} 