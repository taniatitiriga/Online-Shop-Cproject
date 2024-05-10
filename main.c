#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "stock.h"
#include "globals.h"
#include "file.h"

int loginStatus = 1;


int main() {
    int choice;
    int exitCode = 0;
    initializeStock();

    do {

        if (loginStatus) {

            printf("1. View stock\n");
            printf("2. Buy from store\n");
            printf("3. Sell to store\n");
            printf("4. Log out\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    viewStock();
                    break;
                case 2:
                    buyFromStore();
                    break;
                case 3:
                    sellToStore();
                    break;
                case 4:
                    printf("Logging out...\n");
                    loginStatus = 0;
                    break;
                default:
                    printf("Invalid choice. Please enter again.\n");
            }

        } else {

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
