// Luhn's Algorithm checks the validity of bank cards. There is a checksum involved, as well as further validation checks. Below, the program can be run to check
// AMEX, MASTERCARD, and VISA (or INVALID).

// import relevant libaries
#include <cs50.h>
#include <stdio.h>
#include <string.h>

long get_cc_num(void);
int validate_card(long n);
int length_of_num(long n);

int main(void)
{
    // get credit card number from user
    long cc = get_cc_num();

    // validate credit card number
    int result = validate_card(cc);

    // get length of credit card number to determine validity
    int length = length_of_num(cc);

    // ascertain type of card. we also check length of number as further validation.
    if (result == 3 && length == 15)
    {
        printf("AMEX\n");
    }
    else if (result == 4 && (length == 16 || length == 13))
    {
        printf("VISA\n");
    }
    else if (result == 5 && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else {
        printf("INVALID\n");
    }

}

long get_cc_num(void)
{
    // variable to store credit card number from user input
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    return number;
}

int validate_card(long n)
{
    long cc_num = n;

    // set up sum of credit card digits
    int sum;
    // set up variable to store every second number in 'number'
    int temp;
    // add last number in credit card
    sum = cc_num % 10;
    // take last digit off number
    cc_num /= 10;

    // initiate while loop to add each digit of credit card to sum (note: for every other number in credit card, double it and add to 'sum')
    // but if doubled number is > 9, add the digits of that number e.g. if 12, add 1+2 to 'sum', NOT 12
    while (cc_num)
    {
        // double every other digit in credit card number
        temp = (cc_num % 10) * 2;
        if (temp > 9)
        {
            sum += temp - 9;
        }
        else {
            sum += temp;
        }
        // take off the digit we just processed
        cc_num /= 10;
        // store new last digit in temp
        temp = cc_num % 10;
        // add this last digit to sum (we DON'T double it because we only double every other digit)
        sum += temp;
        // get rid of digit that won't be doubled
        cc_num /= 10;
    }

    // get first digit (n1) and first two digits (n2) of credit card number. Note that the first two
    // digits of AMEX and Mastercard matter, but not for VISA.
    long n1 = n, n2 = n;
    while (n)
    {
        n2 = n1;
        n1 = n;
        n /= 10;
    }

    // check if sum is a multiple of 10 (if it is, do further checks on first or first two digits)
    if (sum % 10 != 0)
    {
        return -1;
    }
    else {
        // check first two digits for AMEX
        if (n2 == 34 || n2 == 37)
        {
            return 3;
        }
        // check first two digits for MC
        else if (n2 == 51 || n2 == 52 || n2 == 53 || n2 == 54 || n2 == 55)
        {
            return 5;
        }
        // check first digit for VISA
        else if (n1 == 4)
        {
            return 4;
        }
        // if not any of the above --> invalid
        else {
            return -1;
        }
    }
}

int length_of_num(long n)
{
    int count = 0;
    do {
        n /= 10;
        count++;
    }
    while (n > 0);

    return count;
}

