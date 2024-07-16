#include <stdio.h>
#include <string.h>

#define BITS 8  // Number of bits for the binary numbers

void binary(int num, int bin[]) {
    for (int i = 0; i < BITS; i++) {
        bin[i] = num % 2;
        num /= 2;
    }
}

void print_bin(int bin[]) {
    for (int i = BITS - 1; i >= 0; i--) {
        printf("%d", bin[i]);
    }
}

void twos_complement(int bin[], int comp[]) {
    int carry = 1;
    for (int i = 0; i < BITS; i++) {
        comp[i] = bin[i] == 0 ? 1 : 0;
    }
    for (int i = 0; i < BITS; i++) {
        if (comp[i] == 1 && carry == 1) {
            comp[i] = 0;
        } else {
            comp[i] += carry;
            carry = 0;
        }
    }
}

void binary_addition(int bin1[], int bin2[], int result[]) {
    int carry = 0;
    for (int i = 0; i < BITS; i++) {
        int temp = bin1[i] + bin2[i] + carry;
        result[i] = temp % 2;
        carry = temp / 2;
    }
}

int main() {
    int num1, num2;
    int bin1[BITS] = {0}, bin2[BITS] = {0}, bin2_comp[BITS] = {0}, result[BITS] = {0};

    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    binary(num1, bin1);
    binary(num2, bin2);

    printf("\nBinary of %d: ", num1);
    print_bin(bin1);
    printf("\nBinary of %d: ", num2);
    print_bin(bin2);

    twos_complement(bin2, bin2_comp);
    binary_addition(bin1, bin2_comp, result);

    printf("\n\nResult of binary subtraction: ");
    print_bin(result);
    printf("\n");

    return 0;
}
