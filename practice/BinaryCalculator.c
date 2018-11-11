#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void reverse(char s[]) {
    int i = 0; //sizeof(arr)/sizeof(arr[0) OR
    int j = strlen(s)-1;
    while (i < j) {
        char tmp = s[i];
        s[i++] = s[j];
        s[j--] = tmp;
    }
}

char getHexaChar(int c) {
    switch (c) {
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        default:
            return 'F';
    }
}

int addLeadingDigits(char s[], int size, int i, char leading) {
    int l = strlen(s);
    int j = size - l;
    for (; j > 0 ; j--) {
        s[i++] = leading;
    }
    return i;
}

void addBaseRepresentation(char s[], int i, int b) {
    switch (b) {
        case 2:
            s[i++] = 'b';
            s[i] = '0';
            break;
        case 8:
            s[i++] = 'o';
            s[i] = '0';
            break;
        case 16:
            s[i++] = 'x';
            s[i] = '0';
    }
}

int writeToArray(char s[], int number, int b) {
    int i = 0;
    while (number > 0) {
        int n = number % b;
        if (n > 9) {
            s[i++] = getHexaChar(n);
        } else
            s[i++] = n + '0';
        number /= b;
    }
    return i;
}

/*
 * returns string s containing number in base b
 */
void toBinaryString(int number, char s[], int b) {
    int i = 0;
    int size = sizeof(number) * 2;
    bool isPositive = number > 0 ? true : false;

    if (!isPositive) {
        number = -number;
    }

    i = writeToArray(s, number, b);

    char leading = '0';
    if (!isPositive) {
        leading = '1';
    }

    if (b < 16) {
        i = addLeadingDigits(s, size, i, leading);
    }

    addBaseRepresentation(s, i, b);

    reverse(s);
}