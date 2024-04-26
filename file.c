#include <stdio.h>
#include <string.h>
#include "file.h"

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
