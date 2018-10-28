#include <stdio.h>
#include <zconf.h>

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

void checkSign(int v);
void abs(int v);
void sqrt(int n);

int main() {
    //checkSign(-1);
    //abs(2);
    sqrt(25);
    return 0;
}

void sqrt(int n) {
    int lo = 0;
    int hi = n;
    while (lo <= hi) {
        int m = lo + (hi - lo) / 2;
        if (m*m == n) {
            printf("%d", m);
            return;
        } else if (m*m < n) {
            lo = m + 1;
        } else
            hi = m - 1;
    }
}

void abs(int v) {
    unsigned int r;  // the result goes here
    printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(v));
    printf("\n");
    int const mask = v >> sizeof(int) * CHAR_BIT - 1;
    printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(mask));
    printf("\n");

    r = (v + mask) ^ mask;
    printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(v ^ mask));
    //Patented variation:
    r = (v ^ mask) - mask;
}

void checkSign(int v) {
    int sign;   // the result goes here
    // CHAR_BIT is the number of bits per byte (normally 8).
    sign = -(v < 0);  // if v < 0 then -1, else 0.
    // or, to avoid branching on CPUs with flag registers (IA32):
    sign = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
    // or, for one less instruction (but not portable):
    sign = v >> (sizeof(int) * CHAR_BIT - 1);

    //Alternatively, if you prefer the result be either -1 or +1, then use:
    sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1

    sign = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
    // Or, for more speed but less portability:
    sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));  // -1, 0, or +1
    // Or, for portability, brevity, and (perhaps) speed:
    sign = (v > 0) - (v < 0); // -1, 0, or +1
    
    printf("Sign is: %d", sign);
}