#include "report.h"
#include "inventory.h"
#include "struct.h"
#include "utils.h"
#include "product.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// profit
void profitStatistic() {
	system("cls");
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  💰   PROFIT STATISTICS                    ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	long long totalProfit = 0;
	printf("+============+======================+================+==============+============+==============+\n");
	printf("| %-10s | %-20s | %14s | %12s | %10s | %12s |\n",
	       "SKU", "Name", "Total Exported", "Import Price", "Sell Price", "Profit");
	printf("+============+======================+================+==============+============+==============+\n");
	for (int i = 0; i < productCount; i++) {
		int sumQuantity = 0;
		for (int j = 0; j < transactionCount; j++) {
			if (strcmp(sp[i].sku, gd[j].sku) == 0 && gd[j].type == 1) {
				sumQuantity += gd[j].quantity;
			}
		}
		long long profit = (long long)(sp[i].sellPrice - sp[i].importPrice) * sumQuantity;
		totalProfit += profit;
		printf("| %-10s | %-20s | %14d | %12lld | %10lld | %12lld |\n",
		       sp[i].sku, sp[i].productName, sumQuantity,
		       sp[i].importPrice, sp[i].sellPrice, profit);
	}
	printf("+============+======================+================+==============+============+==============+\n");
	printf("\n💰 Total Profit: %lld VND\n", totalProfit);
}

// filter by caterogy
void filterByCaterogy() {
	char temp[20];
	int choice;

	do {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🗂️    FILTER PRODUCTS BY CATEGORY         ║\n");
		printf("╠════════════════════════════════════════════╣\n");
		printf("║  🍜  1. Food                               ║\n");
		printf("║  🏠  2. Household                          ║\n");
		printf("║  📚  3. School Supplies                    ║\n");
		printf("║  🧸  4. Toy                                ║\n");
		printf("║  🔙  0. Back                               ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		do {
			printf("👉 Enter your choice (0-4): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &choice)) {
				choice = -1;
				continue;
			}
		} while (!checkInputForOptions(choice, 4, "  ❌  Invalid choice! Please enter a number between 0 and 4!\n", "  ✅  Valid choice!\n"));

		switch (choice) {
			case 1:
				system("cls");
				showFood();
				system("pause");
				break;
			case 2:
				system("cls");
				showHousehold();
				system("pause");
				break;
			case 3:
				system("cls");
				showSchoolSupplies();
				system("pause");
				break;
			case 4:
				system("cls");
				showToy();
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

// food
void showFood() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🍜   FOOD PRODUCTS                        ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("+============+======================+======+==============+============+===========+\n");
	printf("| %-10s | %-20s | %4s | %12s | %10s | %9s |\n",
	       "SKU", "Name", "Qty", "Import Price", "Sell Price", "Threshold");
	printf("+============+======================+======+==============+============+===========+\n");
	for (int i = 0; i < productCount; i++) {
		if (strcmp(sp[i].category, "Food") == 0) {
			printf("| %-10s | %-20s | %4d | %12lld | %10lld | %9d |\n",
			       sp[i].sku, sp[i].productName, sp[i].quantity,
			       sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
		}
	}
	printf("+============+======================+======+==============+============+===========+\n");
}

// household
void showHousehold() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🏠   HOUSEHOLD PRODUCTS                   ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("+============+======================+======+==============+============+===========+\n");
	printf("| %-10s | %-20s | %4s | %12s | %10s | %9s |\n",
	       "SKU", "Name", "Qty", "Import Price", "Sell Price", "Threshold");
	printf("+============+======================+======+==============+============+===========+\n");
	for (int i = 0; i < productCount; i++) {
		if (strcmp(sp[i].category, "Household") == 0) {
			printf("| %-10s | %-20s | %4d | %12lld | %10lld | %9d |\n",
			       sp[i].sku, sp[i].productName, sp[i].quantity,
			       sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
		}
	}
	printf("+============+======================+======+==============+============+===========+\n");
}

// School Supplies
void showSchoolSupplies() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📚   SCHOOL SUPPLIES PRODUCTS             ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("+============+======================+======+==============+============+===========+\n");
	printf("| %-10s | %-20s | %4s | %12s | %10s | %9s |\n",
	       "SKU", "Name", "Qty", "Import Price", "Sell Price", "Threshold");
	printf("+============+======================+======+==============+============+===========+\n");
	for (int i = 0; i < productCount; i++) {
		if (strcmp(sp[i].category, "School Supplies") == 0) {
			printf("| %-10s | %-20s | %4d | %12lld | %10lld | %9d |\n",
			       sp[i].sku, sp[i].productName, sp[i].quantity,
			       sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
		}
	}
	printf("+============+======================+======+==============+============+===========+\n");
}

// Toy
void showToy() {
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🧸   TOY PRODUCTS                         ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	printf("+============+======================+======+==============+============+===========+\n");
	printf("| %-10s | %-20s | %4s | %12s | %10s | %9s |\n",
	       "SKU", "Name", "Qty", "Import Price", "Sell Price", "Threshold");
	printf("+============+======================+======+==============+============+===========+\n");
	for (int i = 0; i < productCount; i++) {
		if (strcmp(sp[i].category, "Toy") == 0) {
			printf("| %-10s | %-20s | %4d | %12lld | %10lld | %9d |\n",
			       sp[i].sku, sp[i].productName, sp[i].quantity,
			       sp[i].importPrice, sp[i].sellPrice, sp[i].lowStockThreshold);
		}
	}
	printf("+============+======================+======+==============+============+===========+\n");
}

// Sort product
void sortProduct() {
	system("cls");
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  🔃   SORT PRODUCTS                        ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	for (int i = 0; i < productCount - 1; i ++) {
		for (int j = 0; j < productCount - 1; j ++) {
			if (sp[j].quantity > sp[j + 1].quantity) {
				Product temp = sp[j];
				sp[j] = sp[j + 1];
				sp[j + 1] = temp;
			}
		}
	}

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