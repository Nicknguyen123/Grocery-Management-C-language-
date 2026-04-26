#include <windows.h>
#include "utils.h"
#include "struct.h"
#include "product.h"
#include "fileIO.h"
#include "inventory.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Product sp[10000];
int productCount = 0;

Transaction gd[100000];
int transactionCount = 0;

int main() {

	SetConsoleOutputCP(65001);

	productCount = countProductsInFile();
	readDataForProduct();

	transactionCount = countTransactionsInFile();
	readDataForTransaction();

	char temp[20];
	int choice;
	do {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🏪   MINI GROCERY WAREHOUSE SYSTEM  🏪    ║\n");
		printf("╠════════════════════════════════════════════╣\n");
		printf("║  📦  1. Product Management                 ║\n");
		printf("║  🏬  2. Warehouse Management               ║\n");
		printf("║  📊  3. Report & Statistics                ║\n");
		printf("║  ❌  0. Exit                               ║\n");
		printf("╚════════════════════════════════════════════╝\n");
		do {
			printf("👉 Choose your options (0-3): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &choice)) {
				choice = -1;
				continue;
			}
		} while (!checkInputForOptions(choice, 3, "  ❌  Invalid Number. The number requires in (0-3)\n", "  ✅   Valid Number"));

		switch (choice) {
			case 1: {
				char temp1[20];
				int choice1;
				do {
					system("cls");
					printf("╔════════════════════════════════════════════╗\n");
					printf("║  📦   PRODUCT MANAGEMENT                   ║\n");
					printf("╠════════════════════════════════════════════╣\n");
					printf("║  ➕  1. Add New Product                    ║\n");
					printf("║  ✏️  2. Edit Product                       ║\n");
					printf("║  🗑️  3. Delete Product                     ║\n");
					printf("║  🔍  4. Search Product                     ║\n");
					printf("║  📋  5. Display All Products               ║\n");
					printf("║  🔙  0. Back                               ║\n");
					printf("╚════════════════════════════════════════════╝\n");

					do {
						printf("👉 Choose your options (0-5): ");
						fgets(temp1, sizeof(temp1), stdin);
						temp1[strcspn(temp1, "\n")] = '\0';
						if (!stringToInt(temp1, &choice1)) {
							choice1 = -1;
							continue;
						}
					} while (!checkInputForOptions(choice1, 5, "  ❌  Invalid Number. The number requires in (0-5)\n", "  ✅  Valid Number\n"));

					switch (choice1) {
						case 1:
							addProduct();
							system("pause");
							break;
						case 2:
							editProduct();
							system("pause");
							break;
						case 3:
							deleteProduct();
							system("pause");
							break;
						case 4:
							searchProduct();
							break;
						case 5:
							displayProduct();
							system("pause");
							break;
						case 0:
							printf("\n🔙 Going back to Main Menu...\n\n");
							break;
						default:
							printf("\n  ❌  Invalid choice! Please try again!\n\n");
							break;
					}
				} while (choice1 != 0);
				break;
			}
			case 2: {
				char temp2[20];
				int choice2;
				do {
					system("cls");
					printf("╔════════════════════════════════════════════╗\n");
					printf("║  🏬   WAREHOUSE MANAGEMENT                 ║\n");
					printf("╠════════════════════════════════════════════╣\n");
					printf("║  🔄  1. Update Stock                       ║\n");
					printf("║  📋  2. View Stock Status                  ║\n");
					printf("║  🔔  3. Low Stock Warning                  ║\n");
					printf("║  📜  4. Transaction History                ║\n");
					printf("║  🔙  0. Back                               ║\n");
					printf("╚════════════════════════════════════════════╝\n");

					do {
						printf("👉 Choose your options (0-4): ");
						fgets(temp2, sizeof(temp2), stdin);
						temp2[strcspn(temp2, "\n")] = '\0';
						if (!stringToInt(temp2, &choice2)) {
							choice2 = -1;
							continue;
						}
					} while (!checkInputForOptions(choice2, 4, "  ❌  Invalid Number. The number requires in (0-4)\n", "  ✅  Valid Number\n"));

					switch (choice2) {
						case 1:
							updateStock();
							system("pause");
							break;
						case 2:
							displayStock();
							system("pause");
							break;
						case 3:
							showLowStock();
							system("pause");
							break;
						case 4:
							showTransaction();
							system("pause");
							break;
						case 0:
							printf("\n🔙 Going back to Main Menu...\n\n");
							break;
						default:
							printf("\n  ❌  Invalid choice! Please try again!\n\n");
							break;
					}
				} while (choice2 != 0);
				break;
			}
			case 3: {
				char temp3[20];
				int choice3;
				do {
					system("cls");
					printf("╔════════════════════════════════════════════╗\n");
					printf("║  📊   REPORT & STATISTICS                  ║\n");
					printf("╠════════════════════════════════════════════╣\n");
					printf("║  💰  1. Profit Statistics                  ║\n");
					printf("║  🗂️  2. Filter Products by Category        ║\n");
					printf("║  🔃  3. Sort Products                      ║\n");
					printf("║  📄  4. Export Report to .txt              ║\n");
					printf("║  🔙  0. Back                               ║\n");
					printf("╚════════════════════════════════════════════╝\n");

					do {
						printf("👉 Choose your options (0-4): ");
						fgets(temp3, sizeof(temp3), stdin);
						temp3[strcspn(temp3, "\n")] = '\0';
						if (!stringToInt(temp3, &choice3)) {
							choice3 = -1;
							continue;
						}
					} while (!checkInputForOptions(choice3, 4, "  ❌  Invalid Number. The number requires in (0-4)\n", "  ✅  Valid Number\n"));
					switch (choice3) {
						case 1:
							profitStatistic();
							system("pause");
							break;
						case 2:
							filterByCaterogy();
							break;
						case 3:
							sortProduct();
							system("pause");
							break;
						case 4:
							printf("does not working hihi\n");
							system("pause");
							break;
						case 0:
							printf("\n🔙 Going back to Main Menu...\n\n");
							break;
						default:
							printf("\n  ❌  Invalid choice! Please try again!\n\n");
							break;
					}
				} while (choice3 != 0);
				break;
			}
			case 0:
				printf("\n  👋  Exited Successfully! ✨\n");
				printf("\n  👋  Goodbye! See you next time!\n");
				break;
			default:
				printf("\n  ⚠ Invalid Optionse!\n");
				break;
		}
	} while (choice != 0);

	return 0;
}