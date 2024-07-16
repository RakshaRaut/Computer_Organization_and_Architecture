#include <stdio.h>
#include <math.h>

int q = 0, m = 0, count = 5;
int acc[5] = {0, 0, 0, 0, 0}, qbin[5] = {0}, mbin[5] = {0}, q_1 = 0;

void binary()
{
    // fabs=absolute value
    q = fabs(q);
    m = fabs(m);

    int r, r2;
    // Converting Q and M to binary arrays
    for (int i = 0; i < 5; i++)
    {
        r = q % 2;
        q = q / 2;
        r2 = m % 2;
        m = m / 2;
        qbin[i] = r;
        mbin[i] = r2;
    }
}

void add(int num[])
{
    int temp[5] = {0};
    int i;
    int carry = 0;

    for (i = 0; i < 5; i++)
    {
        temp[i] = acc[i] + num[i] + carry;
        if (temp[i] >= 2)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        temp[i] = temp[i] % 2;
    }
    for (i = 0; i < 5; i++)
    {
        acc[i] = temp[i];
    }
}

void show()
{
    int i;
    for (i = 4; i >= 0; i--)
    {
        printf("%d", acc[i]);
    }
    printf("\t|\t");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
    }
    printf("\t|\t%d", q_1);
}

void arithmetic_right_shift()
{
    int i;
    q_1 = qbin[0];
    for (i = 0; i < 4; i++)
    {
        qbin[i] = qbin[i + 1];
    }
    qbin[4] = acc[0];
    for (i = 0; i < 4; i++)
    {
        acc[i] = acc[i + 1];
    }
    acc[4] = acc[3];
}

void complement(int num[])
{
    int i;
    for (i = 0; i < 5; i++)
    {
        num[i] = 1 - num[i];
    }
    int carry = 1;
    for (i = 0; i < 5; i++)
    {
        num[i] = num[i] + carry;
        if (num[i] >= 2)
        {
            num[i] = num[i] % 2;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}

void main()
{
    int i;
    printf("\t\tBOOTH'S MULTIPLICATION ALGORITHM");
    printf("\nEnter two numbers to multiply: ");
    printf("\nBoth must be less than 16");
    do
    {
        printf("\nEnter multiplicand (M): ");
        scanf("%d", &m);
        printf("Enter multiplier (Q): ");
        scanf("%d", &q);
    } while (q >= 16 || m >= 16);

    printf("\nExpected Product = %d", m * q);

    binary();

    int mcomp[5];
    for (i = 0; i < 5; i++)
    {
        mcomp[i] = mbin[i];
    }
    complement(mcomp);

    printf("\n\nUnsigned Binary Equivalents are: ");
    printf("\nQ = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
    }
    printf("\nM = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", mbin[i]);
    }
    printf("\n-M = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", mcomp[i]);
    }

    printf("\n Constructing Booth's multiplication table\n");
    printf("\n-------------------------------------------------------------");
    printf("\nA\t|\tQ\t|\tQ-1\t|\tCount\t|\tRemarks");
    printf("\n-------------------------------------------------------------\n");

    for (i = 0; i < 5; i++)
    {
        printf("\n");
        show();
        printf("\t|\t%d\t|\tInitial", count);
        if (qbin[0] == 1 && q_1 == 0)
        {
            add(mcomp);
            printf("\n");
            show();
            printf("\t|\t%d\t|\tA = A - M", count);
        }
        else if (qbin[0] == 0 && q_1 == 1)
        {
            add(mbin);
            printf("\n");
            show();
            printf("\t|\t%d\t|\tA = A + M", count);
        }
        arithmetic_right_shift();
        count--;
        printf("\n");
        show();
        printf("\t|\t%d\t|\tRight Shift", count);
    }
    printf("\n-------------------------------------------------------------");
    printf("\nResult = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", acc[i]);
    }
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
    }
    printf("\n");
}
