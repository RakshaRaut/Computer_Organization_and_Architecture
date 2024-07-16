#include <stdio.h>
#include <math.h>

#define BITS 5

void binary(int num, int bin[]) {
    for (int i = 0; i < BITS; i++) {
        bin[i] = num % 2;
        num /= 2;
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

void add(int acc[], int num[]) {
    int carry = 0;
    for (int i = 0; i < BITS; i++) {
        int temp = acc[i] + num[i] + carry;
        acc[i] = temp % 2;
        carry = temp / 2;
    }
}

void shift_left(int acc[], int qbin[]) {
    for (int i = BITS - 1; i > 0; i--) {
        acc[i] = acc[i - 1];
    }
    acc[0] = qbin[BITS - 1];
    for (int i = BITS - 1; i > 0; i--) {
        qbin[i] = qbin[i - 1];
    }
    qbin[0] = 0;
}

void print_bin(int bin[]) {
    for (int i = BITS - 1; i >= 0; i--) {
        printf("%d", bin[i]);
    }
}

void show_state(int acc[], int qbin[], int count, const char* remark) {
    print_bin(acc);
    printf(" | ");
    print_bin(qbin);
    printf(" | %d | %s\n", count, remark);
}

int main() {
    int q, m, qbin[BITS] = {0}, mbin[BITS] = {0}, mcomp[BITS] = {0}, acc[BITS] = {0};
    int sq = 0, sr = 0, count = BITS;

    printf("Enter dividend (Q) and divisor (M) (both < 16): ");
    scanf("%d %d", &q, &m);

    if (q * m < 0) sq = 1;
    if (q < 0) sr = 1;

    binary(fabs(q), qbin);
    binary(fabs(m), mbin);
    twos_complement(mbin, mcomp);

    printf("Binary Q: ");
    print_bin(qbin);
    printf("\nBinary M: ");
    print_bin(mbin);
    printf("\nTwo's Complement of M: ");
    print_bin(mcomp);
    printf("\n\nA | Q | Count | Remarks\n");
    printf("---------------------------------------------\n");

    shift_left(acc, qbin);
    show_state(acc, qbin, count, "Left Shift AQ");

    while (count > 0) {
        add(acc, mcomp);
        show_state(acc, qbin, count, "A <- A - M");

        if (acc[BITS - 1] == 1) {
            qbin[0] = 0;
            add(acc, mbin);
            show_state(acc, qbin, count, "Restore A, Q[0] = 0");
        } else {
            qbin[0] = 1;
            show_state(acc, qbin, count, "Q[0] = 1");
        }

        count--;
        if (count > 0) {
            shift_left(acc, qbin);
            show_state(acc, qbin, count, "Left Shift AQ");
        }
    }

    printf("Remainder: ");
    print_bin(acc);
    printf("\nQuotient: ");
    print_bin(qbin);
    printf("\n");

    return 0;
}
