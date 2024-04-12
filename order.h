#ifndef ORDER_H
#define ORDER_H

#include "product.h"

typedef struct {
    int code;
    char personName[50];
    char personSurname[50];
    Product products[10];
    float amountPaid;
} Order;

#endif