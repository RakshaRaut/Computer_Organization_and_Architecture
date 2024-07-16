#include <stdio.h>
#include <math.h>

int q = 0, m = 0, sq = 0, sr = 0, c = 0;
int acc[5] = {0, 0, 0, 0, 0}, qbin[5] = {0}, mbin[5] = {0}, mcomp[5] = {0};

void binary()
{
    q = fabs(q);
    m = fabs(m);

    int r, r2;
    // Converting Q and M  to binary arrays
    for (int i = 0; i < 5; i++)
    {
        r = q % 2;
        q = q / 2;
        r2 = m % 2;
        m = m / 2;
        qbin[i] = r;
        mbin[i] = r2;
        if (r2 == 0)
        {
            mbin[i] = 0;
        }
        if (r == 0)
        {
            qbin[i] = 0;
        }
    }

    // Taking 2's complement of mcomp
    c = 0;
    for (int i = 0; i < 5; i++)
    {
        if (c == 0)
        {
            mcomp[i] = mbin[i];
            if (mbin[i] == 1)
            {
                c = 1;
            }
            continue;
        }
        if (c == 1)
        {
            if (mbin[i] == 0)
            {
                mcomp[i] = 1;
            }
            if (mbin[i] == 1)
            {
                mcomp[i] = 0;
            }
        }
    }
}

void add(int num[])
{
    int temp[5] = {0};
    int i;
    c = 0;

    for (i = 0; i < 5; i++)
    {
        temp[i] = acc[i] + num[i] + c;
        if (temp[i] >= 2)
        {
            c = 1;
        }
        else
            c = 0;
        temp[i] = temp[i] % 2;
    }
    for (i = 4; i >= 0; i--)
    {
        acc[i] = temp[i];
        printf("%d", acc[i]);
    }
    printf("\t|\t");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
    }
}

void shl()
{
    int i;
    for (i = 4; i > 0; i--)
    { // shift the remainder
        acc[i] = acc[i - 1];
    }
    acc[0] = qbin[4];
    for (i = 4; i > 0; i--)
    { // shift the remtient
        qbin[i] = qbin[i - 1];
    }
    qbin[0] = 0;
    for (i = 4; i >= 0; i--)
    {
        printf("%d", acc[i]);
    }
    printf("\t|\t");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
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
}

void main()
{
    int i, count = 5;
    printf("\t\tRESTORING DIVISION ALGORITHM");
    printf("\nEnter two numbers to divide: ");
    printf("\nBoth must be less than 16");
    do
    {
        printf("\nEnter dividend (Q): ");
        scanf("%d", &q);
        printf("Enter divisor (M): ");
        scanf("%d", &m);
    } while (q >= 16 || m >= 16);

    printf("\nExpected Quotient = %d", q / m);
    printf("\nExpected Remainder = %d", q % m);

    if (q * m < 0)
    {
        sq = 1;
    }
    if (q < 0)
    {
        sr = 1;
    }
    binary();
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
    printf("\nM'+ 1 = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", mcomp[i]);
    }
    printf("\n Constructing Restoring division table\n");
    printf("\n-------------------------------------------------------------");
    printf("\nA\t|\tQ\t|\tCount\t|\tRemarks\t");
    printf("\n-------------------------------------------------------------\n");
    // division part
    shl();
    printf("\t|\t%d\t|\tLeft Shift AQ", count);
    for (i = 0; i < 5; i++)
    {
        printf("\n");
        add(mcomp);
        printf("\t|\t%d\t|\t A <- A - M", count);
        printf("\n");

        if (acc[4] == 1)
        { // simply add for restoring
            qbin[0] = 0;
            add(mbin);
            printf("\t|\t%d\t|\t RESTORE A,Q[0]=0 ", count);
        }
        else
        {
            qbin[0] = 1;
            show();
            printf("\t|\t%d\t|\t Q[0]=1 ", count);
        }
        count = count - 1;
        printf("\n-------------------------------------------------------------");
        if (i < 4)
        {
            printf("\n");
            shl();
            printf("\t|\t%d\t|\tLeft Shift AQ", count);
        }
    }
    printf("\n-------------------------------------------------------------");
    printf("\nSign of the remainder = %d", sr);
    printf("\nRemainder is = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", acc[i]);
    }
    printf("\nSign of the Quotient = %d", sq);
    printf("\nQuotient is = ");
    for (i = 4; i >= 0; i--)
    {
        printf("%d", qbin[i]);
    }
    printf("\n");
}