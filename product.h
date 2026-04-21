#ifndef PRODUCT_H
#define PRODUCT_H

void addProduct();
int checkOverlapsSku(char *s);
void editProduct();
void supportEdit(int index);
void editName(int index);
void editCaterogy(int index);
void editImportPrice(int index);
void editSellPrice(int index);
void editLowStockThreshold(int index);
void deleteProduct();
void supportDelete(int index);
void searchProduct();
int searchBySku();
void searchByName();
void displayProduct();

#endif