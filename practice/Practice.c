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

void reverse() {
    int i = 0; //sizeof(arr)/sizeof(arr[0) OR
    int j = 9;
    while (arr[--j] != '\n') {
        ;
    }
    --j;
    while (i < j) {
        char tmp = arr[i];
        arr[i++] = arr[j];
        arr[j--] = tmp;
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

int main() {
    char s[] = "0x7fabc";
    htoi(s);
    return 0;
}

