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

// Update stock
void updateStock() {
	char temp[20];
	char yesNo;

	while (1) {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🔄    UPDATE STOCK                        ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		int found = searchBySku();

		if (found != -1) {
			do {
				printf("🔄  Do you want to update stock with product above? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				supportUpdate(found);
				system("cls");
				writeData1("  ✅  Quantity saved successfully!\n");
				writeData2("  ✅  Transaction saved successfully!\n");

				do {
					printf("🔄  Do you want to update stock with another product? (Y/N): ");
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
				printf("🔄  Do you want to edit another product? (Y/N): ");
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

void supportUpdate(int index) {
	char temp[10];
	int choice;

	do {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  🔄    UPDATE STOCK                        ║\n");
		printf("╠════════════════════════════════════════════╣\n");
		printf("║  📥  0. Import                             ║\n");
		printf("║  📤  1. Export                             ║\n");
		printf("║  🔙  2. Back                               ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		do {
			printf("👉 Choose your options (0-2): ");
			fgets(temp, sizeof(temp), stdin);
			temp[strcspn(temp, "\n")] = '\0';
			if (!stringToInt(temp, &choice)) {
				choice = -1;
				continue;
			}
		} while (!checkInputForOptions(choice, 2, "  ❌  Invalid Number. The number requires in (0-2)\n", "  ✅  Valid Number\n"));

		switch (choice) {
			case 0:
				system("cls");
				import(index);
				system("pause");
				break;
			case 1:
				system("cls");
				export(index);
				system("pause");
				break;
			case 2:
				break;
			default:
				printf("\n  ❌  Invalid choice! Please try again!\n\n");
				break;
		}
	} while (choice != 2);
}

// Import product;
void import(int index) {
	char temp[20];
	int tempQuantity;
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📥   IMPORT STOCK                         ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	sprintf(gd[transactionCount].transactionId, "TX%06d", transactionCount + 1);
	strcpy(gd[transactionCount].sku, sp[index].sku);
	gd[transactionCount].type = 0;

	int validQuantity = 1000 - sp[index].quantity;

	do {
		printf("📦 Enter Quantity (1 - %d): ", validQuantity);
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		if (!stringToInt(temp, &tempQuantity)) {
			tempQuantity = -1;
			continue;
		}
	} while (!checkInputForUpdateStock(tempQuantity, validQuantity));

	gd[transactionCount].quantity = tempQuantity;
	gd[transactionCount].timestamp = time(NULL);
	transactionCount ++;
	sp[index].quantity = sp[index].quantity + tempQuantity;

	printf("  ✅  Import stock successfully! %s: %d → %d\n", sp[index].productName, sp[index].quantity - tempQuantity, sp[index].quantity);
}

// export product
void export(int index) {
	char temp[20];
	int tempQuantity;
	printf("╔════════════════════════════════════════════╗\n");
	printf("║  📤   EXPORT STOCK                         ║\n");
	printf("╚════════════════════════════════════════════╝\n");

	sprintf(gd[transactionCount].transactionId, "TX%06d", transactionCount + 1);
	strcpy(gd[transactionCount].sku, sp[index].sku);
	gd[transactionCount].type = 1;

	do {
		printf("📦 Enter Quantity (1 - %d): ", sp[index].quantity);
		fgets(temp, sizeof(temp), stdin);
		temp[strcspn(temp, "\n")] = '\0';
		if (!stringToInt(temp, &tempQuantity)) {
			tempQuantity = -1;
			continue;
		}
	} while (!checkInputForUpdateStock(tempQuantity, sp[index].quantity));

	gd[transactionCount].quantity = tempQuantity;
	gd[transactionCount].timestamp = time(NULL);
	transactionCount ++;
	sp[index].quantity = sp[index].quantity - tempQuantity;

	printf("  ✅  Export stock successfully! %s: %d → %d\n", sp[index].productName, sp[index].quantity + tempQuantity, sp[index].quantity);
}

// transaction history
void showTransaction() {
	char temp[20];
	char yesNo;
	while (1) {
		system("cls");
		printf("╔════════════════════════════════════════════╗\n");
		printf("║  📜   TRANSACTION HISTORY                  ║\n");
		printf("╚════════════════════════════════════════════╝\n");

		int found = searchBySku();

		if (found != -1) {
			do {
				printf("📜  Do you want to see transaction history of product above? (Y/N): ");
				fgets(temp, sizeof(temp), stdin);
				temp[strcspn(temp, "\n")] = '\0';
				yesNo = temp[0];
			} while (!checkInputForYN(yesNo));

			if (yesNo == 'Y' || yesNo == 'y') {
				showTransaction1(found);

				do {
					printf("📜  Do you want to see transaction history of another product? (Y/N): ");
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
				printf("📜  Do you want to see transaction history of another product? (Y/N): ");
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

void showTransaction1(int index) {
	system("cls");
	printf("╔══════════════╦══════════════╦══════════╦══════════╦═════════════════════╗\n");
	printf("║ TransactionID║     SKU      ║   Type   ║   Qty    ║      Timestamp      ║\n");
	printf("╠══════════════╬══════════════╬══════════╬══════════╬═════════════════════╣\n");
	for (int i = 0; i < transactionCount; i++) {
		if (strcmp(gd[i].sku, sp[index].sku) == 0) {
			char timeStr[20];
			struct tm *t = localtime(&gd[i].timestamp);
			strftime(timeStr, sizeof(timeStr), "%d/%m/%Y %H:%M:%S", t);
			printf("║ %-12s ║ %-12s ║ %-8s ║ %8d ║ %-19s ║\n", gd[i].transactionId, gd[i].sku, 
			gd[i].type == 0 ? "Import" : "Export", gd[i].quantity, timeStr);
		}
	}
	printf("╚══════════════╩══════════════╩══════════╩══════════╩═════════════════════╝\n");
}