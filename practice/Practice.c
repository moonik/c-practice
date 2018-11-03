#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP  20

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
    int c;
    int newLines = 0;
    int blanks = 0;
    int tabs = 0;
    while((c = getchar()) != EOF) {
        if(c == '\n') {
            ++newLines;
        } else if(c == '\t') {
            ++tabs;
        } else if(c == ' ') {
            ++blanks;
        }
    }
    printf("New lines = %d\n", newLines);
    printf("Tabs = %d\n", tabs);
    printf("Blanks = %d\n", blanks);
}

int main() {
    readChar();
    return 0;
}

