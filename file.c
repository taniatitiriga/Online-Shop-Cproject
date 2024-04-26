#include <stdio.h>
#include <string.h>
#include "file.h"
#include "stock.h"

#define MAX_PRODUCTS 100

//__________________________________PASSWORD ENCRYPTION__________________________________

char rot13(char c) {
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M')) {
        return c + 13;
    } else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z')) {
        return c - 13;
    } else {
        return c;
    }
}

void encrypt13(char *password) {
    int i;
    for (i = 0; password[i] != '\0'; i++) {
        password[i] = rot13(password[i]);
    }
}


//__________________________________ACCOUNTS FILE__________________________________

int writeAccountToFile(char *firstName, char *username, char *password) {
    encrypt13(password);

    FILE *file = fopen("localAccounts.txt", "a");
    if (file == NULL) {
        file = fopen("localAccounts.txt", "w");
        if (file == NULL) {
            perror("Error creating file");
            return 0;
        }
    }

    fprintf(file, "%s %s %s\n", firstName, username, password);
    fclose(file);
    return 1;
}

int checkLogin(char *username, char *password) {
    encrypt13(password);

    FILE *file = fopen("localAccounts.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        char storedUsername[50];
        char storedPassword[50];
        sscanf(buffer, "%*s %s %s", storedUsername, storedPassword);
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

//__________________________________STOCK FILE__________________________________

void initializeStock() {
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {

        // initialize file
        file = fopen("stock.txt", "w");
        if (file == NULL) {
            perror("Error creating file");
            return;
        }

        // define default products
        Product defaultProducts[] = {
                {10000, "Product1", 10, 5.99},
                {10001, "Product2", 20, 8.99},
                // add more...
        };
        int numDefaultProducts = sizeof(defaultProducts) / sizeof(defaultProducts[0]);

        // write default products to file
        for (int i = 0; i < numDefaultProducts && i < MAX_PRODUCTS; i++) {
            fprintf(file, "%d %s %d %.2f\n", defaultProducts[i].code, defaultProducts[i].name,
                    defaultProducts[i].quantity, defaultProducts[i].price);
        }

        fclose(file);
    }
}
