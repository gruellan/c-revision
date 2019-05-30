#include <stdio.h>
#include <string.h>

// Two ways to calculate string length (has come up in exams before)

int string_length_array(char string[]) {
    int index = 0;

    while(string[index] != '\0') {
        index++;
    }
    return index;
}

int string_length_pointer_enhanced(char string[]) {
    char *p = string;

    while (*p != '\0'){
        p++;
    }

    return p-string;
}

int string_length_pointer(char string[]) {
    char *p = string;
    int index = 0;

    while (*p != '\0') {
        // increment string length
        index++;

        // pointer now points to the next array element
        p++;
    }
    return index;
}

int main() {
    char *s= "hello";
    printf("String, %s, has length %d\n", s, string_length_array(s));
    printf("String, %s, has length %d\n", s, string_length_pointer(s));    
    printf("String, %s, has length %d\n", s, string_length_pointer_enhanced(s));
    int m = -4;
}