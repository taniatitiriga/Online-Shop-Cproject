#include <stdio.h>
#include <string.h>
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

        while (fscanf(file, "%d %s %d %lf", &tempCode, name, &tempQuantity, &price)  == 4) {
            printf("%d %s %d %.2f\n", tempCode, name, tempQuantity, price);
            if (tempCode == code) {
                found = 1;
                printf("Product found in stock.\n");
                printf("Product Name: %s\n", name);
                printf("Price: %.2f\n", price);
                printf("Enter the quantity to add: ");
                scanf("%d", &quantity);
                tempQuantity += quantity;
                printf("Total quantity: %d, %d\n", tempQuantity, quantity);
            }
            fprintf(file, "%05d %s %d %.2f\n", tempCode, name, tempQuantity, price);
        }
        fclose(file);

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

    FILE *file = fopen("stock.txt", "r+");
    if (file == NULL) {
        perror("Error opening stock file");
        return;
    }

    int found = 0;
    int tempCode, tempQuantity;
    char name[50];
    double price;

    long int pos = ftell(file);
    while (fscanf(file, "%d %s %d %lf", &tempCode, name, &tempQuantity, &price) == 4) {
        if (tempCode == code) {
            found = 1;
            if (tempQuantity >= quantity) {
                tempQuantity -= quantity;
                fseek(file, pos, SEEK_SET);
                fprintf(file, "\n%05d %s %d %.2f", tempCode, name, tempQuantity, price);
                printf("Product bought from store.\n");
            } else {
                quantity = 0;
                fseek(file, pos, SEEK_SET);
                fprintf(file, "\n%05d %s %d %.2f", tempCode, name, quantity, price);
                printf("Not enough quantity available (bought %d pieces).\n", tempQuantity);
            }
            break;
        }
        pos = ftell(file);
    }

    if (!found) {
        printf("Product code does not exist.\n");
    }

    fclose(file);
}
