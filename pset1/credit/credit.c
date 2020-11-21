#include <stdio.h>
#include <cs50.h>

// Declaration of functions used, defined below main
long long pow10(int exp);
int checksum(int array_size);
long long ccnum;

int main()
{
    int sum;
    ccnum = get_long_long("Number: ");

    // AMEX Validation...
    if (ccnum / pow10(13) == 34 || ccnum / pow10(13) == 37)
    {
        sum = checksum(15); // AMEX is 15 digits, starting with 34 or 37
        if (sum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // MASTERCARD Validation...
    else if (ccnum / pow10(14) > 50 && ccnum / pow10(14) < 56)
    {
        sum = checksum(16); // MASTERCARD is 16 digits, starting with 51 to 55

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // VISA 13 Validation...
    else if (ccnum / pow10(12) == 4)
    {
        sum = checksum(13); // VISA could be 13 digits, starting with 4
        if (sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // VISA 16 Validation
    else if (ccnum / pow10(15) == 4)
    {
        sum = checksum(16); // OR VISA could be 16 digits, starting with 4
        if (sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Added functions
/*
Function to calculate exponents:
simply multiplying 10 by exp times
*/
long long pow10(int exp)
{
    int base = 10;
    long long result = 1;

    while (exp != 0)
    {
        result *= base;
        exp--;
    }
    return result;
}

// Checksum Function: takes in the array size for the card digits
int checksum(int array_size)
{
    int ccnumdgit[array_size];
    int i = array_size - 1;

    /*
    Assigning values to array elements - from RIGHT TO LEFT
    by extracting the digits of ccnum, one by one
    */
    while (i > -1)
    {
        ccnumdgit[i] = ccnum % 10;
        ccnum /= 10;
        i--;
    }

    /*
    Take the sum of the digits not multiplied by 2,
    starting from the last digit, moving every other digit towards the first (second digit as last)
    */
    i = array_size - 1;
    int sum1 = 0;
    while (i > -1)
    {
        sum1 += ccnumdgit[i];
        i = i - 2;
    }

    /*
    Take the sum of the digits to be multiplied by 2,
    starting from the second to the last digit, moving every other digit towards the first (first digit as last)
    */
    i = array_size - 2;
    int sum2 = 0;
    while (i > -1)
    {
        if (2 * ccnumdgit[i] > 9)
        {
            int ccnumdgit2 = 2 * ccnumdgit[i];
            sum2 += ((ccnumdgit2 / 10) + (ccnumdgit2 % 10)) ;
        }
        else
        {
            sum2 += 2 * ccnumdgit[i];
        }

        i = i - 2;
    }
    return sum1 + sum2;
}