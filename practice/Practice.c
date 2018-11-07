#include <stdio.h>
#include <stdbool.h>

#define LOWER       0
#define UPPER       300
#define STEP        20
#define ASCII_CHARS 127
#define TAB_STOP    8
#define SPLIT_COL   10

int wordLengths[1024];
int chars[ASCII_CHARS];
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
    while(arr[i] != '\n') {
        if(arr[i] == '\t') {
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
    while(arr[i] != '\n') {
        arr[j++] = arr[i];
        arr[i++] = '\0';
    }
    arr[j] = '\n';
}

void entab() {
   int i = 0;
   int sCounter = 0;
   while(arr[i] != '\n') {
       if(arr[i] == ' ') {
           sCounter++;
       }
       if(sCounter == 8) {
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
    while (arr[i] != '\n') {
        if(c == SPLIT_COL) {
            if(arr[i] != '\t' && arr[i] != ' ') {
                arr[i] = '-';
                shiftRight(i);
            }
            arr[++i] = '\n';
            c = 0;
        }
        i++;
        c++;
    }
}

int main() {
    //readChar();
    int c;
    int i = 0;
    while((c = getchar()) != 48) {
        arr[i++] = c;
    }
    //detab();
    //entab();
    //reverse();
    foldLongInput();
    for (int j = 0; arr[j] != '\0'; ++j) {
        printf("%c", arr[j]);
    }
    return 0;
}

