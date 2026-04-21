#include "struct.h"
#include "utils.h"
#include "product.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readDataForProduct() {
	FILE *f = fopen("dataofproducts.bin", "rb");
	if (f == NULL) {
		printf("Error opening file\n");
		return;
	}
	fread(sp, sizeof(Product), productCount, f);
	fclose(f);
}

void readDataForTransaction() {
	FILE *f = fopen("dataoftransactions.bin", "rb");
	if (f == NULL) {
		printf("Error opening file\n");
		return;
	}
	fread(gd, sizeof(Transaction), transactionCount, f);
	fclose(f);
}

void writeData(char *s) {
    FILE *f = fopen("dataofproducts.bin", "ab");
    if (f == NULL) {
        printf("  ❌  Error opening file\n");
        return;
    }
    fwrite(&sp[productCount - 1], sizeof(Product), 1, f);
    fclose(f);
    printf("%s", s);
}

void writeData1(char *s) {
    FILE *f = fopen("dataofproducts.bin", "wb");
    if (f == NULL) {
        printf("  ❌  Error opening file\n");
        return;
    }
    fwrite(sp, sizeof(Product), productCount, f);
    fclose(f);
    printf("%s", s);
}

int countProductsInFile() {
	FILE *f = fopen("dataofproducts.bin", "rb");
	if (f == NULL) {
		printf("Error opening file or file does not exist\n");
		return 0;
	}

	// Di chuyển con trỏ file đến cuối file
	fseek(f, 0, SEEK_END);

	// Lấy vị trí hiện tại (= kích thước file)
	long fileSize = ftell(f);

	// Tính số lượng sinh viên
	int count = fileSize / sizeof(Product);

	fclose(f);
	return count;
}

int countTransactionsInFile() {
	FILE *f = fopen("dataoftransactions.bin", "rb");
	if (f == NULL) {
		printf("Error opening file or file does not exist\n");
		return 0;
	}

	// Di chuyển con trỏ file đến cuối file
	fseek(f, 0, SEEK_END);

	// Lấy vị trí hiện tại (= kích thước file)
	long fileSize = ftell(f);

	// Tính số lượng sinh viên
	int count = fileSize / sizeof(Transaction);

	fclose(f);
	return count;
}