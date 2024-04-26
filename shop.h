#ifndef SHOP_H
#define SHOP_H

#include "order.h"
#include "product.h"
#include "fileIO.h"

extern Order orders[];
extern int orderCount;

extern Product products[];
extern int productCount;

void login(char *name, char *surname);
void placeOrder(Order *orders, int *orderCount);
void sellProduct(Product *products, int *productCount);
void viewOrders(Order *orders, int orderCount);
void searchProducts(Product *products, int productCount);

void readProductsFromFile(const char* filePath);
void writeProductsToFile(const char* filePath, const char* message);
void readOrdersFromFile(const char* filePath);
void writeOrdersToFile(const char* filePath, const char* message);

#endif