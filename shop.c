#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shop.h"
#include "constants.h"
#include "fileIO.h"

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100

Product products[MAX_PRODUCTS];
int productCount = 0;

Order orders[MAX_ORDERS];
int orderCount = 0;

void login(char *name, char *surname) {
    printf("Welcome, %s %s!\n", name, surname);
    printf("Logged in successfully!\n");
}

void placeOrder(Order *orders, int *orderCount) {
    printf("Placing an order...\n");
    Order newOrder;
    newOrder.code = *orderCount + 1;
    strcpy(newOrder.personName, "John");
    strcpy(newOrder.personSurname, "Doe");
    printf("Enter product name: ");
    scanf("%s", newOrder.products[0].name);
    int e = 0;
    printf("Products found:");
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, newOrder.products[0].name) != NULL) {
            e=1;
            printf("Product Name: %s, Quantity: %d, Price: %.2f\n", products[i].name, products[i].quantity, products[i].price);
        }
    }
    if(e==0){
        printf("No product named ' %s ' in our stock yet.\n",newOrder.products[0].name);
    }

    printf("Enter quantity: ");
    scanf("%d", &newOrder.products[0].quantity);
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, newOrder.products[0].name) != NULL) {
            e=1;
        }
    }
    if(e==0){
        printf("Product ' %s ' not in our stock\n",newOrder.products[0].name);
    }

    orders[*orderCount] = newOrder;
    (*orderCount)++;
    printf("Order placed successfully!\n");
}

void sellProduct(Product *products, int *productCount) {
    printf("Selling a product to the store...\n");
    Product newProduct;
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Enter price: ");
    scanf("%f", &newProduct.price);

    products[*productCount] = newProduct;
    (*productCount)++;
    printf("Product added to store successfully!\n");
}

void viewOrders(Order *orders, int orderCount) {
    printf("Viewing placed orders...\n");
    if (orderCount == 0) {
        printf("No orders placed yet.\n");
        return;
    }
    printf("Orders:\n");
    for (int i = 0; i < orderCount; i++) {
        printf("Order Code: %d, Person: %s %s, Amount Paid: %.2f\n",
               orders[i].code, orders[i].personName, orders[i].personSurname);
        printf("Products:\n");
        for (int j = 0; j < sizeof(orders[i].products) / sizeof(orders[i].products[0]); j++) {
            printf("\tProduct Name: %s, Quantity: %d, Price: %.2f\n",
                   orders[i].products[j].name, orders[i].products[j].quantity, orders[i].products[j].price);
        }
    }
}

void searchProducts(Product *products, int productCount) {
    printf("Searching for products...\n");
    char keyword[50];
    scanf("%s", keyword);

    printf("Search Results:\n");
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, keyword) != NULL) {
            printf("Product Name: %s, Quantity: %d, Price: %.2f\n",
                   products[i].name, products[i].quantity, products[i].price);
        }
    }
}

void readProductsFromFile(const char* filePath) {
    readFromCSV(filePath);
}

void writeProductsToFile(const char* filePath, const char* message) {
    writeToFile(filePath, message);
}

void readOrdersFromFile(const char* filePath) {
    readFromCSV(filePath);
}

void writeOrdersToFile(const char* filePath, const char* message) {
    writeToFile(filePath, message);
}