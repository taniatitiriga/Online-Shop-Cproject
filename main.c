#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "globals.h"

int loginStatus = 0;

int main() {
    int choice;
    int exitCode = 0;

    do {

        if (loginStatus) {

        #if defined (_WIN32) || defined(_WIN64)
        system("cls"); // windows
        #else
        system("clear"); // linux or macOS
        #endif

            printf("1. View stock\n");
            printf("2. Buy from store\n");
            printf("3. Sell to store\n");
            printf("4. Log out\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    //print stock
                    break;
                case 2:
                    //buy
                    break;
                case 3:
                    //sell
                    break;
                case 4:
                    printf("Logging out...\n");
                    loginStatus = 0;
                    break;
                default:
                    printf("Invalid choice. Please enter again.\n");
            }

        } else {

        #if defined (_WIN32) || defined(_WIN64)
        system("cls"); // windows
        #else
        system("clear"); // linux or macOS
        #endif

            printf("1. Log in\n");
            printf("2. Create account\n");
            printf("3. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    createAccount();
                    break;
                case 3:
                    printf("Exiting...\n");
                    exitCode = 1;
                    break;
                default:
                    printf("Invalid choice. Please enter again.\n");
            }
        }
    } while (exitCode != 1);

    return 0;
}
