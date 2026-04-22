#ifndef STRUCT_H
#define STRUCT_H
#include <time.h>

typedef struct {
    char sku[20];
    char productName[50];
    char category[50];
    int quantity;
    long long importPrice;
    long long sellPrice;
    int lowStockThreshold;
} Product;

extern Product sp[10000];
extern int productCount; 

typedef struct {
    char transactionId[20];
    char sku[20];
    int type;
    int quantity;
    time_t timestamp;
} Transaction;

extern Transaction gd[100000];
extern int transactionCount;

#endif