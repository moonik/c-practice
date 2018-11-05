#include <stdio.h>
#include <stdbool.h>

#define LOWER       0
#define UPPER       300
#define STEP        20
#define ASCII_CHARS 127
int wordLengths[1024];
int chars[ASCII_CHARS];
char arr[10];

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
    int wLength = 0;
    int j = 0;
    while((c = getchar()) != 48) {
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
    int i = 0;
    int j = 9;
    while(arr[--j] != '\n') {
        ;
    }
    --j;
    while(i < j) {
        char tmp = arr[i];
        arr[i++] = arr[j];
        arr[j--] = tmp;
    }
}

int main() {
    //readChar();
    int c;
    int i = 0;
    while((c = getchar()) != 48) {
        arr[i++] = c;
    }
    reverse();
    for (int j = 0; arr[j] != '\n'; ++j) {
        printf("%c", arr[j]);
    }
    return 0;
}

