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