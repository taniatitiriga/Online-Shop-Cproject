#include <stdio.h>
#include "stock.h"
#include "globals.h"


void viewStock() {
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Product Code  |  Product Name  |  Quantity  |  Price (EUR)\n");
    printf("----------------------------------------------------------\n");

    int code;
    char name[50];
    int quantity;
    double price;

    while (fscanf(file, "%d %s %d %lf", &code, name, &quantity, &price) != EOF) {
        printf("%-13d | %-14s | %-10d | %.2f\n", code, name, quantity, price);
    }

    fclose(file);
}

void sellToStore() {
    int code, quantity;
    printf("Enter the product code (or 0 for new product): ");
    scanf("%d", &code);

    if (code == 0) {
        FILE *file = fopen("stock.txt", "r");
        int lastCode = 0;
        if (file != NULL) {
            int line_count = 0;
            char ch;
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '\n') {
                    line_count++;
                }
            }
            fclose(file);

            code = BASE_PRODUCT_CODE + line_count;

            char name[50];
            double price;
            printf("Enter the product name: ");
            scanf("%s", name);
            printf("Enter the quantity: ");
            scanf("%d", &quantity);
            printf("Enter the price: ");
            scanf("%lf", &price);

            FILE *newProductFile = fopen("stock.txt", "a");
            if (newProductFile == NULL) {
                perror("Error opening file");
                return;
            }
            fprintf(newProductFile, "%05d %s %d %.2f\n", code, name, quantity, price);
            fclose(newProductFile);

            printf("New product added to stock.\n");
        } else {
            printf("Error opening file\n");
            return;
        }
    } else {
        FILE *file = fopen("stock.txt", "r+");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }

        int found = 0;
        int tempCode, tempQuantity;
        char name[50];
        double price;

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            perror("Error opening file");
            fclose(file);
            return;
        }

        while (fscanf(file, "%d %s %d %lf", &tempCode, name, &tempQuantity, &price) != EOF) {
            if (tempCode == code) {
                found = 1;
                printf("Product found in stock.\n");
                printf("Product Name: %s\n", name);
                printf("Price: %.2f\n", price);
                printf("Enter the quantity to add: ");
                scanf("%d", &quantity);
                tempQuantity += quantity; // Increase quantity
            }
            fprintf(tempFile, "%05d %s %d %.2f\n", tempCode, name, tempQuantity, price);
        }

        fclose(file);
        fclose(tempFile);

        remove("stock.txt");
        rename("temp.txt", "stock.txt");

        if (!found) {
            printf("Product code does not exist.\n");
            return;
        }

        printf("Quantity updated in stock.\n");
    }
}

void buyFromStore() {
    int code, quantity;
    printf("Enter the product code: ");
    scanf("%d", &code);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // update stock if enough quantity available
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    int found = 0;
    int tempCode, tempQuantity;
    char name[50];
    double price;

    while (fscanf(file, "%d %s %d %lf", &tempCode, name, &tempQuantity, &price) != EOF) {

        if (tempCode == code) {
            found = 1;
            if (tempQuantity >= quantity) {
                tempQuantity -= quantity;
            } else {
                quantity = tempQuantity; // only sell available quantity
                tempQuantity = 0;
            }
        }
        fprintf(tempFile, "%d %s %d %.2f\n", tempCode, name, tempQuantity, price);
    }

    fclose(file);
    fclose(tempFile);

    remove("stock.txt");
    rename("temp.txt", "stock.txt");

    if (found) {
        printf("Product bought from store.\n");
    } else {
        printf("Product code does not exist.\n");
    }
}
