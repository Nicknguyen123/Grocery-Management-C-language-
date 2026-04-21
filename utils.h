#ifndef UTILS_H
#define UTILS_H

int stringToInt(const char *str, int *out);
int stringToLongLong(const char *str, long long *out);
int checkInputForOptions(int choice, int n, char *s1, char *s2);
int checkInputForSku(char *s);
int checkInputForName(char *s, char *s1);
int checkInputForCaterogy(char *s, char *s1);
int checkInputForPrice(long long price);
int checkInputForYN(char yesNo);
void convertUppercase(char *s);
void convertLowercase(char *s);
void beautifyString(char *s);

#endif