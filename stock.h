#ifndef STOCK_H
#define STOCK_H

#define MAX_PRODUCTS 100

typedef struct {
    int code;
    char name[50];
    int quantity;
    double price;
} Product;

void viewStock();
void sellToStore();
void buyFromStore();

#endif
