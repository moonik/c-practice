#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

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

typedef char* String;
typedef struct person {
    String name;
    int age;
    union salary {
        int iSalary;
        float fSalary;
        String sSalary;
        int type;
    } salary;
    unsigned int gender: 1;
} Person;

extern void toBinaryString(int number, char s[], int b);
extern void recursiveFormatter(int number, String s, int b);

void sayHello(void (*say)());
void printString();
void printInt();
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

void testPointer(String s) {
    for (int i = 0; i < 10; ++i) {
        *s = i + '0';
        s++;
    }
}

void pointerexp() {
    char s[256];
    testPointer(s);
    printf("%s", s);
}

void experiment() {
    int s[] = {1, 9, 3, 4};
    int *p = s;
    int c = *p++;
    int c2 = --*p;
    printf("%d", c2);
}

void appendString(String str1, String str2) {
    while (*str1) {
        str1++;
    }
    while ((*str1++ = *str2++)) {
        ;
    }
}

/*
 * returns 1 if the string str2 occurs at the end of the string str1, and zero otherwise
 */
int isAtTheEnd(String str1, String str2) {
    unsigned index = (unsigned) (strlen(str1) - strlen(str2));
    while (str1[index]) {
        if (str1[index] != *str2) {
            return 0;
        }
        index++;
        str2++;
    }
    return 1;
}

/*
 *  copies at most n characters of t to s.
 */
void copyTo(String s, String t, unsigned n) {
    while (*s) {
        s++;
    }
    while (n > 0) {
        *s++ = *t++;
        n--;
    }
}

/*
 * compares from first n chars of string s with t
 * returns 1 if equal and 0 if otherwise
 */

int compare(String s, String t, unsigned n) {
    while (n > 0) {
        if (*s++ != *t++) {
            return 0;
        }
        n--;
    }
    return 1;
}

static void reverse(String s) {
    char *right = &s[strlen(s)-1];
    char *left = s;
    while (left < right) {
        char tmp = *right;
        *right-- = *left;
        *left++ = tmp;
    }
}

void sort() {
    char firstWord[] = "abcde";
    char secondWord[] = "a";
    char thirdWord[] = "bc";
    char *pointers[255];

    pointers[0] = firstWord;
    pointers[1] = secondWord;
    pointers[2] = thirdWord;

    //pointers[3] = "\0";

    for (int i = 0; i < 3; i++) {
        for (int j = i; j > 0; j--) {
            int first = strlen(pointers[j]);
            int second = strlen(pointers[j-1]);
            if (second < first) {
                char *tmp = pointers[j];
                pointers[j] = pointers[j-1];
                pointers[j-1] = tmp;
            } else
                break;
        }
    }
    for (int k = 0; k < 3; ++k) {
        printf("%s\n", pointers[k]);
    }
}

void sayHello(void (*say)()) {
    (*say)();
}

void printString() {
    printf("Aloha");
}

void printInt() {
    printf("123");
}

void saySomething(bool isInt) {
    if (isInt) {
        sayHello((void (*)()) printInt);
    } else
        sayHello((void (*)()) printString);
}

void sortStruct(Person* family, int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = i; j > 0; j--) {
            if (family[j].age < family[j-1].age) {
                struct person tmp = family[j];
                family[j] = family[j-1];
                family[j-1] = tmp;
            } else
                break;
        }
    }
}

void printSalary(Person* p) {
    if (p->salary.type == 0) {
        printf("salary: %d\n", p->salary.iSalary);
    } else if (p->salary.type == 1) {
        printf("%f\n", p->salary.fSalary);
    } else
        printf("%s\n", p->salary.sSalary);
}

int main() {
    return 0;
}