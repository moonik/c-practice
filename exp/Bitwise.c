#include <stdio.h>
#include <zconf.h>
#include <stdbool.h>

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
int checkIfOppositeSign(int x, int y);
int extendSign(int x);
int signExtendingWithBitWidth(int x);
void setOrClearBits();
void printBinary(int n);
void merge(int a, int b, int mask);

int main() {
    //checkSign(-1);
    //abs(2);
    //sqrt(25);
    //printf("%d", checkIfOppositeSign(1, 1));
    //signExtendingWithBitWidth(-3);
    setOrClearBits();
    return 0;
}

// a - value to merge in non-masked bits
// b - // value to merge in masked bits
// mask - 1 where bits from b should be selected; 0 where from a.
void merge(int a, int b, int mask) {
    unsigned int r;    // result of (a & ~mask) | (b & mask) goes here

    r = a ^ ((a ^ b) & mask);
}

void setOrClearBits() {
    bool f = false;         // conditional flag
    unsigned int m = 12; // the bit mask
    unsigned int w = 9879; // the word to modify:  if (f) w |= m; else w &= ~m;

    w ^= (-f ^ w) & m;

    // OR, for superscalar CPUs:
    w = (w & ~m) | (-f & m);
}

void printBinary(int n) {
    while (n) {
        if (n & 1)
            printf("1");
        else
            printf("0");

        n >>= 1;
    }
}

signExtendingWithBitWidth(int x) {
    unsigned b; // number of bits representing the number in x
    int r;      // resulting sign-extended number
    int const m = 1U << (b - 1); // mask can be pre-computed if b is fixed

    x = x & ((1U << b) - 1);  // (Skip this if bits in x above position b are already zero.)
    r = (x ^ m) - m;
    return r;
}

int extendSign(int x) { // convert this from using 5 bits to a full int
    int r; // resulting sign extended number goes here
    struct {signed int x:5;} s;
    r = s.x = x;
    return r;
}

int checkIfOppositeSign(int x, int y) {
    return (x ^ y) < 0;
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