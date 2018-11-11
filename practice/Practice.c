#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define LOWER       0
#define UPPER       300
#define STEP        20
#define ASCII_CHARS 127
#define TAB_STOP    8
#define SPLIT_COL   10
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

extern toBinaryString(int number, char s[], int b);
extern recursiveFormater(int number, char s[], int b);

char arr[255];

/*
 * Practice exercises from book The c programming language 2
 */

/**
 * converts Fahrenheit to Celsius
 */
void fahrenheitToCelsius() {
    float fahr, celsius;

    fahr = UPPER;

    printf("Temperature conversion table\n");
    printf("Fahrenheit\tCelsius\n");
    while (fahr >= LOWER) {
        celsius = (5.0f/9.0f) * (fahr - 32.0f);
        printf("%3.0f \t\t%6.1f\n", fahr, celsius);
        fahr -= STEP;
    }
}

/**
 *
 * reads char from input
 */
void readChar() {
    int wordLengths[1024] = {};
    int chars[ASCII_CHARS] = {};
    int c;
    int wLength = 0;
    int j = 0;
    while ((c = getchar()) != 48) {
        ++chars[c-'0'];
        if (c == ' ' || c == '\t' || c == '\n') {
            wordLengths[j++] = wLength;
            wLength = 0;
        } else
            ++wLength;
    }
    printf("Word lengths:\n");
    for (int i = 0; wordLengths[i] != 0; ++i) {
        for (int k = 0; k < wordLengths[i]; ++k) {
            printf("|");
        }
        printf("\n");
    }
    printf("\nCharacter frequencies:\n");
    for (int l = 0; l <ASCII_CHARS; ++l) {
        printf("%c = %d\n", '0'+l, chars[l]);
    }
}

void shiftRight(int i) {
    char prev = arr[i++];
    for (; arr[i] != '\n'; ++i) {
        char tmp = arr[i];
        arr[i] = prev;
        prev = tmp;
    }
    arr[i] = prev;
    arr[i+1] = '\n';
}

void detab() {
    int i = 0;
    while (arr[i] != '\n') {
        if (arr[i] == '\t') {
            for (int j = 1; j < TAB_STOP; ++j) {
                arr[i++] = ' ';
                shiftRight(i);
            }
            arr[i++] = ' ';
        }
        i++;
    }
}

void shiftLeft(int i) {
    int j = i-7;
    while (arr[i] != '\n') {
        arr[j++] = arr[i];
        arr[i++] = '\0';
    }
    arr[j] = '\n';
}

void entab() {
    int i = 0;
    int sCounter = 0;
    while (arr[i] != '\n') {
        if (arr[i] == ' ') {
            sCounter++;
        }
        if (sCounter == 8) {
            arr[i-sCounter+1] = '\t';
            shiftLeft(i+1);
            sCounter = 0;
        }
        i++;
    }
}

void foldLongInput() {
    int c = 0;
    int i = 0;
    int sIndex = 0;
    while (arr[i] != '\000') {
        if (c == SPLIT_COL) {
            if (arr[i] != '\t' && arr[i] != ' ') {
                if (i - sIndex > 2) {
                    shiftRight(i);
                    arr[i] = '-';
                    shiftRight(i+1);
                    arr[i+1] = '\n';
                } else
                    arr[sIndex] = '\n';
            } else
                arr[i] = '\n';
            c = -1;
        }
        if (arr[i] == ' ' || arr[i] == '\t' || arr[i] == '\n') {
            sIndex = i;
        }
        i++;
        c++;
    }
}

void removeComments() {
    int i = 0;
    char n[255];
    int j = 0;
    while (arr[i] != '\000') {
        if (arr[i] == '/' && arr[i+1] == '/') {
            while (arr[++i] != '\n') {
                ;
            }
            i++;
        }
        if (arr[i] == '/' && arr[i+1] == '*') {
            bool isEnd = false;
            while (!isEnd) {
                if (arr[i] == '*' && arr[i+1] == '/') {
                    isEnd = true;
                }
                i += 3;
            }
        }
        n[j++] = arr[i];
        i++;
    }
    for (int k = 0; n[k] != '\000'; ++k) {
        printf("%c", n[k]);
    }
}

char getOpenChar(char closingChar) {
    switch (closingChar) {
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
        case '"':
            return '"';
        default:
            return '\'';
    }
}

void checkSyntax() {
    char stack[255] = {};
    char quotes[10] = {};
    int q = 0;
    int s = 0;
    int i = 0;
    while(arr[i] != '\000') {
        switch(arr[i]) {
            case '(':
            case '{':
            case '[':
                stack[s++] = arr[i];
                break;
            case ')':
            case '}':
            case ']':
                if(stack[s-1] == getOpenChar(arr[i])) {
                    s--;
                }
                break;
            case '"':
                if(quotes[q-1] != '"') {
                    quotes[q++] = arr[i];
                } else
                    q--;
                break;
            case '\'':
                if(quotes[q-1] != '\'') {
                    quotes[q++] = arr[i];
                } else
                    q--;
                break;
        }
        i++;
    }
    if(s == 0 && q == 0) {
        printf("Success!");
    } else
        printf("Error!");
}

/*
 * converts hexadecimal string to decimal value
 */
void htoi(char str[]) {
    int length = strlen(str);
    int i = 0;
    int number = 0;
    int power = length-1;
    if (length > 2) {
        if (str[1] == 'x' || str[1] == 'X') {
            i = 2;
            power -= 2;
        }
    }
    while (str[i] != '\0') {
        int p = pow(16, power--);
        if (str[i]-'0' > 9) {
            number += (toupper(str[i])-57+2) * p; // converts from A...F to int value
        } else
            number += (str[i]-'0') * p;
        i++;
    }
    printf("%d", number);
}

void readFromConsole() {
    int c;
    int i = 0;
    while ((c = getchar()) != 48) {
        arr[i++] = c;
    }
}

void printArray() {
    for (int j = 0; arr[j] != '\000'; ++j) {
        printf("%c", arr[j]);
    }
}

/*
 * returns n bits from position p
 */
unsigned getBits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

/*
 * eturns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 */
unsigned setBits(unsigned x, int p, int n, unsigned y) {
    return x & ~(~(~0 << n) << (p+1-n)) | ( y & ~(~0<<n)) << (p+1-n);
}

unsigned invert(unsigned x, int p, int n) {
    int invertMask = 0xFF >> (p-1);
    int mask = 0 << n;
    return ((invertMask ^ mask) << (p-1)) ^ x;
}

unsigned rotr(unsigned x, unsigned n) {
    return (x >> n % 32) | (x << (32-n) % 32);
}

double stringToFloat(const char s[]) {
    double value;
    double power;
    double exponent = 1;
    int i = 0;
    int sign = s[i] == '-' ? -1 : 1;
    for (value = 0.0; s[i] > '0' && s[i] < '9'; i++) {
        value = 10.0 * value + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; s[i] > '0' && s[i] < '9'; i++) {
        value = 10.0 * value + (s[i] - '0');
        power *= 10.0;
    }

    if (strlen(s) > i && s[i++] == 'e') {
        int eSign = s[i] == '-' ? -1 : 1;
        if (eSign < 0) {
            i++;
        }
        int n = 0;
        for (; s[i] != '\0'; ++i) {
            n = n*10 + (s[i] - '0');
        }
        exponent = pow(10, eSign * n);
    }
    return (sign * value / power) * exponent;
}

int main() {
    char s[256];
    recursiveFormater(3, s, 2);
    //toBinaryString(3, s, 2);
    printf("%s\n", s);
    //printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(-64));
    return 0;
}