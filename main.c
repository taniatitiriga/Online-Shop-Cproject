#include <stdio.h>
#include <stdlib.h>
#include "shop.h"
#include "constants.h"

extern int orderCount;
extern int productCount;

int main() {
    const char* productsFilePath = "products.csv";
    const char* ordersFilePath = "orders.csv";

    readProductsFromFile(productsFilePath);
    readOrdersFromFile(ordersFilePath);

    int choice;
    do {
        printf("\n________ MENU ________\n");
        printf("1. Login\n");
        printf("2. Place Order\n");
        printf("3. Sell Products to Store\n");
        printf("4. View Placed Orders\n");
        printf("5. Search Products\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50], surname[50];
                printf("Enter your name: ");
                scanf("%s", name);
                printf("Enter your surname: ");
                scanf("%s", surname);
                login(name, surname);
                break;
            }
            case 2:
                placeOrder(orders, &orderCount);
                break;
            case 3:
                sellProduct(products, &productCount);
                break;
            case 4:
                viewOrders(orders, orderCount);
                break;
            case 5:
                searchProducts(products, productCount);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    writeProductsToFile(productsFilePath, "New product data");
    writeOrdersToFile(ordersFilePath, "New order data");

    return 0;
}