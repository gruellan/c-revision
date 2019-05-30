// Has been asked in exams before
#include <stdio.h>
#include <string.h>

int isPalindrome(char string[]) {
    int len = strlen(string);
    for (int i = 0; i<len; i++) {
        if (string[i] != string[len-i-1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char input[20];

    printf("Enter a word: ");
    scanf("%s", input);
    int ans = isPalindrome(input);

    if (ans == 1) {
        printf("%s is palindromic.\n", input);
    }
    else {
        printf("%s is NOT palindromic.\n", input);
    }
}