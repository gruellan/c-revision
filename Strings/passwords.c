#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Returns 1 if valid, return 0 if invalid
int validatePassword(char input[]) {
    // Check new password for any integers
    for (int i=0; i<=strlen(input); i++) {
        if (isdigit(input[i]) == 1) {
            return 1;
        }
    }

    // Validate password length
    if (strlen(input) >= 8) {
        return 1;
    }
    else {
        return 0;
    }
}

// Gets new password input from user and passes it into validation function
int changePassword(char password[]) {
    char input[20];
    printf("New password: ");
    scanf("%s", input);
    if (validatePassword(input) != 1) {
        do {
            printf("New password is not valid.\n");
            printf("New password: ");
            scanf("%s", input);
        } while(validatePassword(input) != 1);
    }
    if(validatePassword(input) == 1) {
        printf("Successfully changed!\n");
    }
}

int main() {
    char password[] = "GeorgesPassword1";
    char input[20];
    int correct = 0;
    char answer;

    printf("Enter your password: ");
    scanf("%s", input);

    // Verify if input is correct, if not then keep trying
    do {
    if (strcmp(input, password)==0) {
        correct = 1;
        printf("Correct!\n");
    }
    else {
        printf("Try again.\n");
        scanf("%s",input);
    }
    } while(correct == 0);

    // Asks user if they want to change password
    if (correct == 1) {
        printf("Do you want to change your password? (y/n)\n");
        // Scan for user's input
        while(answer != 'y' && answer != 'n'){
            scanf("%c", &answer);
        }

        if (answer == 'y') {
            changePassword(password);
        }
        if (answer == 'n') {
            printf("Okay, good bye!\n");
        }
    }

}