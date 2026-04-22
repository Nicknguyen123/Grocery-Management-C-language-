#include "struct.h"
#include "utils.h"
#include "product.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// add product
void addProduct() {

	char temp[20];
	char yesNo;

	while (1) {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  ➕   ADD NEW PRODUCT                      ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		printf("📝 Please enter the product information below:\n");
		printf("⚠️ SKU format: SKU + 6 digits (e.g. SKU000001)\n\n");
		printf("  ────────────────────────────────────────\n");
		printf("  📦 Adding Product #%d\n", productCount + 1);
		printf("  ────────────────────────────────────────\n");

		Product newProduct;
		do {
			printf("🔑 Enter ID Product (SKU): ");
			fgets(newProduct.sku, sizeof(newProduct.sku), stdin);
			newProduct.sku[strcspn(newProduct.sku, "\n")] = '\0';
			convertUppercase(newProduct.sku);
		} while (!checkInputForSku(newProduct.sku) || !checkOverlapsSku(newProduct.sku));


		do {
			printf("📝 Enter Product Name: ");
			fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
			newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';
			beautifyString(newProduct.productName);
		} while (!checkInputForName(newProduct.productName, "  ✅  Valid product name!\n"));

		do {
			printf("🗂️ Enter Category (Food, Household, School Supplies, Toy): ");
			fgets(newProduct.category, sizeof(newProduct.category), stdin);
			newProduct.category[strcspn(newProduct.category, "\n")] = '\0';
			beautifyString(newProduct.category);
		} while (!checkInputForCaterogy(newProduct.category, "  ✅  Valid caterogy!\n"));

		do {
			printf("📦 Enter Quantity (0 - 1000): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &newProduct.quantity)) {
				newProduct.quantity = -1;
				continue;
			}
		} while (!checkInputForOptions(newProduct.quantity, 1000, "  ❌  Invalid quantity! Please enter a number between 0 and 1000!\n", "  ✅  Valid quantity!\n"));

		do {
			printf("💵 Enter Import Price (1000 - 2.000.000): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToLongLong(temp, &newProduct.importPrice)) {
				newProduct.importPrice = -1;
				continue;
			}
		} while (!checkInputForPrice(newProduct.importPrice));

		do {
			printf("💰 Enter Sell Price (1000 - 2.000.000): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToLongLong(temp, &newProduct.sellPrice)) {
				newProduct.sellPrice = -1;
				continue;
			}
		} while (!checkInputForPrice(newProduct.sellPrice));

		do {
			printf("🔔 Enter Low Stock Threshold (0 - 333): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &newProduct.lowStockThreshold)) {
				newProduct.lowStockThreshold = -1;
				continue;
			}
		} while (!checkInputForOptions(newProduct.lowStockThreshold, 333,
		                               "  ❌  Invalid threshold! Please enter a number between 0 and 333!\n", "  ✅  Valid threshold!\n"));

		sp[productCount] = newProduct;
		productCount ++;
		writeData("  ✅  Product added successfully!\n");

		do {
			printf("➕ Do you want to add another product? (Y/N): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			yesNo = temp[0];
		} while (!checkInputForYN(yesNo));

		if (yesNo == 'Y' || yesNo == 'y') {
			continue;
		} else {
			break;
		}
	}
}

int checkOverlapsSku(char *s) {
	for (int i = 0; i < productCount; i ++) {
		if (strcmp(s, sp[i].sku) == 0) {
			printf("  ❌  SKU already exists! Please enter another SKU!\n");
			return 0;
		}
	}
	return 1;
}

// Edit product
void editProduct() {
	char temp[20];
	char yesNo;
	while (1) {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  ✏️    EDIT PRODUCT                        ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		int found = searchBySku();

		if (found != -1) {
			do {
				printf("✏  Do you want to edit this product? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				supportEdit(found);
				system("cls");
				writeData1("  ✅  Product edited successfully!\n");

				do {
					printf("✏  Do you want to edit another product? (Y/N): ");
					fgets(temp, sizeof(temp), stdin);
					temp[strcspn(temp, "\n")] = '\0';
					yesNo = temp[0];
				} while (!checkInputForYN(yesNo));

				if (yesNo == 'Y' || yesNo == 'y') {
					continue;
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			do {
				printf("✏  Do you want to edit another product? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				continue;
			} else {
				break;
			}
		}
	}
}

void supportEdit(int index) {
	char temp[10];
	int choice;

	do {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  ✏️    EDIT PRODUCT                        ║\n");
		printf("╠════════════════════════════════════════════╣\n");
		printf("║  📝  1. Edit Product Name                  ║\n");
		printf("║  🗂️  2. Edit Category                      ║\n");
		printf("║  💵  3. Edit Import Price                  ║\n");
		printf("║  💰  4. Edit Sell Price                    ║\n");
		printf("║  🔔  5. Edit Low Stock Threshold           ║\n");
		printf("║  🔙  0. Back                               ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		do {
			printf("👉 Choose your options (0-5): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &choice)) {
				choice = -1;
				continue;
			}
		} while (!checkInputForOptions(choice, 5, "  ❌  Invalid Number. The number requires in (0-5)\n", "  ✅  Valid Number\n"));

		switch (choice) {
			case 1:
				system("cls");
				editName(index);
				system("pause");
				break;
			case 2:
				system("cls");
				editCaterogy(index);
				system("pause");
				break;
			case 3:
				system("cls");
				editImportPrice(index);
				system("pause");
				break;
			case 4:
				system("cls");
				editSellPrice(index);
				system("pause");
				break;
			case 5:
				system("cls");
				editLowStockThreshold(index);
				system("pause");
				break;
			case 0:
				break;
			default:
				printf("\n  ❌  Invalid choice! Please try again!\n\n");
				break;
		}
	} while (choice != 0);
}

void editName(int index) {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📝   EDIT PRODUCT NAME                    ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("📋 Current Name: %s\n\n", sp[index].productName);

	do {
		printf("📝 Enter new Product Name: ");
		fgets(sp[index].productName, sizeof(sp[index].productName), stdin);
		sp[index].productName[strcspn(sp[index].productName, "\n")] = '\0';
		beautifyString(sp[index].productName);
	} while (!checkInputForName(sp[index].productName, "  ✅  Valid product name!\n"));

	printf("  ✅  Product name updated successfully!\n");
}

void editCaterogy(int index) {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🗂️    EDIT CATEGORY                       ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("📋 Current Category: %s\n\n", sp[index].category);

	do {
		printf("🗂️ Enter new Category (Food / Household / School Supplies / Toy): ");
		fgets(sp[index].category, sizeof(sp[index].category), stdin);
		sp[index].category[strcspn(sp[index].category, "\n")] = '\0';
		beautifyString(sp[index].category);
	} while (!checkInputForCaterogy(sp[index].category, "  ✅  Valid caterogy!\n"));

	printf("  ✅  Category updated successfully!\n");
}

void editImportPrice(int index) {
	char temp[20];
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  💵   EDIT IMPORT PRICE                    ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("📋 Current Import Price: %lld VND\n\n", sp[index].importPrice);

	do {
		printf("💵 Enter new Import Price (1000 - 2.000.000): ");
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		if (!stringToLongLong(temp, &sp[index].importPrice)) {
			sp[index].importPrice = -1;
			continue;
		}
	} while (!checkInputForPrice(sp[index].importPrice));

	printf("  ✅  Import price updated successfully!\n");
}

void editSellPrice(int index) {
	char temp[20];
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  💰   EDIT SELL PRICE                      ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("📋 Current Sell Price: %lld VND\n\n", sp[index].sellPrice);

	do {
		printf("💰 Enter new Sell Price (1000 - 2.000.000): ");
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		if (!stringToLongLong(temp, &sp[index].sellPrice)) {
			sp[index].sellPrice = -1;
			continue;
		}
	} while (!checkInputForPrice(sp[index].sellPrice));

	printf("  ✅  Sell price updated successfully!\n");
}

void editLowStockThreshold(int index) {
	char temp[20];
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🔔   EDIT LOW STOCK THRESHOLD             ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("📋 Current Low Stock Threshold: %d\n\n", sp[index].lowStockThreshold);

	do {
		printf("🔔 Enter new Low Stock Threshold (0 - 333): ");
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		if (!stringToInt(temp, &sp[index].lowStockThreshold)) {
			sp[index].lowStockThreshold = -1;
			continue;
		}
	} while (!checkInputForOptions(sp[index].lowStockThreshold, 333,
	                               "  ❌  Invalid threshold! Please enter a number between 0 and 333!\n", "  ✅  Valid threshold!\n"));

	printf("  ✅  Low stock threshold updated successfully!\n");
}

// delete product
void deleteProduct() {
	char temp[20];
	char yesNo;

	while (1) {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🗑️   DELETE PRODUCT                       ║\n");
		printf("╚════════════════════════════════════════════╝\n");
		printf("⚠️ Note: Only products with quantity = 0 can be deleted!\n\n");

		int found = searchBySku();
		if (found != -1) {
			do {
				printf("🗑  Do you want to delete this product? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				if (sp[found].quantity == 0) {
					supportDelete(found);
					writeData1("  ✅  Product deleted successfully!\n");
				} else {
					printf("  ❌  Cannot delete! Product still has stock in warehouse!\n");
					printf("⚠  Please export all stock before deleting this product!\n");
				}

				do {
					printf("🗑  Do you want to delete another product? (Y/N): ");
					fgets(temp, sizeof(temp), stdin);
					temp[strcspn(temp, "\n")] = '\0';
					yesNo = temp[0];
				} while (!checkInputForYN(yesNo));

				if (yesNo == 'Y' || yesNo == 'y') {
					continue;
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			do {
				printf("🗑  Do you want to delete another product? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				continue;
			} else {
				break;
			}
		}
	}
}

void supportDelete(int index) {
	for (int i = index; i < productCount - 1; i ++) {
		sp[i] = sp[i + 1];
	}
	productCount --;
}

// Search Product
void searchProduct() {
	char temp[20];
	int choice;
	do {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🔍   SEARCH PRODUCT                       ║\n");
		printf("╠════════════════════════════════════════════╣\n");
		printf("║  🔑  1. Search by SKU                      ║\n");
		printf("║  📝  2. Search by Name                     ║\n");
		printf("║  🔙  0. Back                               ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		do {
			printf("👉 Enter your choice (0-2): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &choice)) {
				choice = -1;
				continue;
			}
		} while (!checkInputForOptions(choice, 2, "  ❌  Invalid choice! Please enter a number between 0 and 2!\n", "  ✅  Valid choice!\n"));

		switch (choice) {
			case 1: {
				system("cls");
				int index = searchBySku();
				system("pause");
				break;
			}
			case 2:
				system("cls");
				searchByName();
				system("pause");
				break;
			case 0:
				break;
			default:
				printf("\n  ❌  Invalid choice! Please try again!\n\n");
				break;
		}
	} while (choice != 0);
}

int searchBySku() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🔑   SEARCH PRODUCT BY SKU                ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("📝 Please enter the SKU you want to search:\n");
	printf("⚠  SKU format: SKU + 6 digits (e.g. SKU000001)\n\n");

	char temp[20]; 

	do {
		printf("🔑 Enter SKU: ");
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		convertUppercase(temp);  
	} while (!checkInputForSku(temp));

	for (int i = 0; i < productCount; i++) {
		if (strcmp(sp[i].sku, temp) == 0) {
			printf("  ✅  Product found!\n\n");
			printf("+============+======================+=================+======+==============+==============+===========+\n");
			printf("| %-10s | %-20s | %-15s | %4s | %12s | %12s | %9s |\n", "SKU", "Name", "Category", "Qty", "Import Price", 
			"Sell Price", "Threshold");
			printf("+============+======================+=================+======+==============+==============+===========+\n");
			printf("| %-10s | %-20s | %-15s | %4d | %12lld | %12lld | %9d |\n", sp[i].sku, sp[i].productName, sp[i].category, 
			sp[i].quantity, sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
			printf("+============+======================+=================+======+==============+==============+===========+\n");
			return i;
		}
	}

	printf("  ❌  Product not found! Please check the SKU and try again!\n");
	return -1;
}

void searchByName() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📝   SEARCH PRODUCT BY NAME               ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("  📝  Please enter the Name you want to search:\n");
	printf("  ⚠️   Search is case-insensitive (e.g. hao hao = Hao Hao)\n\n");

	char temp[50];
	int found;

	do {
		printf("📝 Enter Product Name: ");
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
	} while (!checkInputForName(temp, "  ✅  Valid product name!\n"));

	beautifyString(temp);

	for (int i = 0; i < productCount; i++) {
		if (strstr(sp[i].productName, temp)) {
			if (found == 0) {
				printf("  ✅  Product found!\n\n");
				printf("+============+======================+==================+======+==============+==============+===========+\n");
				printf("| %-10s | %-20s | %-16s | %4s | %12s | %12s | %9s |\n", "SKU", "Name", "Category", "Qty",
				       "Import Price", "Sell Price", "Threshold");
				printf("+============+======================+==================+======+==============+==============+===========+\n");
			}
			printf("| %-10s | %-20s | %-16s | %4d | %12lld | %12lld | %9d |\n",
			       sp[i].sku, sp[i].productName, sp[i].category,
			       sp[i].quantity, sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
			found = 1;
		}
	}
	if (found == 1) {
		printf("+============+======================+==================+======+==============+==============+===========+\n");
	} else {
		printf("  ❌  Product not found! Please check the Name and try again!\n");
	}
}

//Display all Product

void displayProduct() {
	system("cls");
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📋   DISPLAY ALL PRODUCTS                 ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("+============+======================+==================+======+==============+==============+===========+\n");
	printf("| %-10s | %-20s | %-16s | %4s | %12s | %12s | %9s |\n",
	       "SKU", "Name", "Category", "Qty", "Import Price", "Sell Price", "Threshold");
	printf("+============+======================+==================+======+==============+==============+===========+\n");

	for (int i = 0; i < productCount; i++) {
		printf("| %-10s | %-20s | %-16s | %4d | %12lld | %12lld | %9d |\n",
		       sp[i].sku, sp[i].productName, sp[i].category,
		       sp[i].quantity, sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
	}

	printf("+============+======================+==================+======+==============+==============+===========+\n");
}