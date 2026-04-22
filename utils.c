#include "struct.h"
#include "utils.h"
#include "product.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

int stringToInt(const char *str, int *out) {
    char *end;
    errno = 0;
    long val = strtol(str, &end, 10);

    if (end == str || *end != '\0') return 0;
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) return 0;

    *out = (int)val;
    return 1;
}

int stringToLongLong(const char *str, long long *out) {
    char *end;
    errno = 0;
    long long val = strtoll(str, &end, 10);
    if (end == str || *end != '\0') return 0;
    if (errno == ERANGE) return 0;
    *out = val;
    return 1;
}

int checkInputForOptions(int choice, int n, char *s1, char *s2) {
	if (!(choice >= 0 && choice <= n)) {
		printf("%s", s1);
		return 0;
	}
	printf("%s", s2);
	return 1;
}

int checkInputForUpdateStock(int choice, int n) {
	if (!(choice >= 1 && choice <= n)) {
		printf("  ❌  Invalid quantity! Please enter a number between 1 and %d!\n", n);
		return 0;
	}
	printf("  ✅  Valid quantity!\n");
	return 1;
}

int checkInputForSku(char *s) {
    if (strlen(s) != 9) {
        printf("  ❌  Invalid SKU! Must be exactly 9 characters (e.g. SKU000001)\n");
        return 0;
    }
    if (strncmp("SKU", s, 3) != 0) {
        printf("  ❌  Invalid SKU! Must start with 'SKU' (e.g. SKU000001)\n");
        return 0;
    }
    for (int i = 3; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) {
            printf("  ❌  Invalid SKU! Last 6 characters must be digits (e.g. SKU000001)\n");
            return 0;
        }
    }
    printf("  ✅  Valid SKU format!\n");
    return 1;
}

int checkInputForName(char *s, char *s1) {
    if (strlen(s) == 0) {
        printf("  ❌  Input cannot be empty!\n");
        return 0;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i]) && !isdigit(s[i]) && !isspace(s[i])) {
            printf("  ❌  Invalid input! Only letters, digits and spaces are allowed!\n");
            return 0;
        }
    }
    printf("%s", s1);
    return 1;
}

int checkInputForCaterogy(char *s, char *s1) {
    if (strlen(s) == 0) {
        printf("  ❌  String cannot be empty!\n");
        return 0;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i]) && !isdigit(s[i]) && !isspace(s[i])) {
            printf("  ❌  Invalid input! Only letters, digits and spaces are allowed!\n");
            return 0;
        }
    }
    if (strcmp("Food", s) != 0 && strcmp("Household", s) != 0 && strcmp("School Supplies", s) != 0 && strcmp("Toy", s) != 0) {
        printf("  ❌  Invalid category! Must be: Food / Household / School Supplies / Toy\n");
        return 0;
    }
    printf("%s", s1);
    return 1;
}

int checkInputForPrice(long long price) {
    if (!(price >= 1000 && price <= 2000000)) {
        printf("  ❌  Invalid price! Please enter a price between 1,000 and 2,000,000 VND!\n");
        return 0;
    }
    printf("  ✅  Valid price!\n");
    return 1;
}

int checkInputForYN(char yesNo) {
    if (yesNo != 'Y' && yesNo != 'y' && yesNo != 'N' && yesNo != 'n') {
        printf("  ❌  Invalid input! Please enter Y or N only!\n");
        return 0;
    }
    printf("  ✅  Valid input!\n");
    return 1;
}

void convertUppercase(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = toupper(s[i]);
    }
}

void convertLowercase(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = tolower(s[i]);
    }
}

void beautifyString(char *s) {
    // xóa khoảng trắng đầu
    int i = 0;
    while (isspace(s[i])) {
        i++;
    }
    int j = 0;
    while (s[i] != '\0') {
        s[j] = s[i];
        j++;
        i++;
    }
    s[j] = '\0';

    // xóa khoảng trắng cuối
    int end = strlen(s) - 1;
    while (end >= 0 && isspace(s[end])) {
        s[end] = '\0';
        end--;
    }

    // chuẩn hóa khoảng trắng giữa
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace(s[i])) {
            int temp = i;
            while (isspace(s[temp])) {
                temp++;
            }
            for (int j = i + 1; s[j - 1] != '\0'; j++) {
                s[j] = s[temp];
                temp++;
            }
        }
    }

    // in hoa chữ cái đầu mỗi từ
    convertLowercase(s);
    s[0] = toupper(s[0]);
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace(s[i])) {
            s[i + 1] = toupper(s[i + 1]);
        }
    }
}