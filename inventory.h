#ifndef INVENTORY_H
#define INVENTORY_H

void updateStock();
void supportUpdate(int index);
void import(int index);
void export(int index);
void displayStock();
void showLowStock();
int countProductWithLowQuantity();
void showTransaction();
void showTransaction1();

#endif
