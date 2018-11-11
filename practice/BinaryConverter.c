#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void format(int number, char *s, int b) {
    if (number == 0) {
        return;
    }
    int n = number % b;
    number /= b;
    format(number, s+1, b);
    *s = n + '0';
}

void recursiveFormatter(int number, char *s, int b) {
    bool isPositive = number > 0 ? true : false;
    if (!isPositive) {
        number = -number;
        *s = '1';
        s++;
    }
    format(number, s, b);
    //*s = '\0'; -- when set the string is empty
}

//void format(int number, char *s[], int *i, int b) {
//    if (number == 0) {
//        return;
//    }
//    int n = number % b;
//    number /= b;
//    format(number, s, i, b);
//    (*s)[(*i)++] = n + '0';
//}
//
//void recursiveFormater(int number, char s[], int b) {
//    int i = 0;
//
//    bool isPositive = number > 0 ? true : false;
//    if (!isPositive) {
//        number = -number;
//        s[i++] = '1';
//    }
//    format(number, &s, &i, b);
//    s[i] = '\0';
//}

void reverse(char s[]) {
    int i = 0;
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

void addLeadingDigits(char s[], int size, int *i, char leading) {
    int l = strlen(s);
    int j = size - l;
    for (; j > 0 ; j--) {
        s[(*i)++] = leading;
    }
}

void addBaseRepresentation(char s[], int *i, int b) {
    switch (b) {
        case 2:
            s[(*i)++] = 'b';
            s[*i] = '0';
            break;
        case 8:
            s[(*i)++] = 'o';
            s[*i] = '0';
            break;
        case 16:
            s[(*i)++] = 'x';
            s[*i] = '0';
    }
}

void writeToArray(char s[], int number, int b, int *i) {
    while (number > 0) {
        int n = number % b;
        if (n > 9) {
            s[(*i)++] = getHexaChar(n);
        } else
            s[(*i)++] = n + '0';
        number /= b;
    }
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

    writeToArray(s, number, b, &i);

    char leading = '0';
    if (!isPositive) {
        leading = '1';
    }

    if (b == 2 || b == 3) {
        addLeadingDigits(s, size, &i, leading);
    }

    addBaseRepresentation(s, &i, b);

    reverse(s);

    s[++i] = '\0';
}