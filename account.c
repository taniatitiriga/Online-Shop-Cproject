#include <stdio.h>
#include <string.h>
#include "account.h"
#include "file.h"

void createAccount() {
    char firstName[50];
    char username[50];
    char password[50];

    printf("Enter your first name: ");
    scanf("%s", firstName);

    printf("Enter a username: ");
    scanf("%s", username);

    printf("Enter a password: ");
    scanf("%s", password);

    if (writeAccountToFile(firstName, username, password)) {
        printf("Account created successfully!\n");
    } else {
        printf("Failed to create account. Please try again later.\n");
    }
}

void login() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (checkLogin(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password.\n");
    }

}
