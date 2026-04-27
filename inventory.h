#ifndef INVENTORY_H
#define INVENTORY_H

void updateStock();
void supportUpdate(int index);
void importStock(int index);
void exportStock(int index);
void displayStock();
void showLowStock();
int countProductWithLowQuantity();
void showTransaction();
int searchSkuInTransaction();
void showTransaction1();

#endif
