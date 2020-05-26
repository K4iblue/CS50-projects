// Luhn's Algorithm
// 1. Multiply every other Digit by 2, starting with the second-to-last digit, add those products digits together
// 2. Add the sum, to the sum of the digits that weren't multiplied
// 3. If the total's last digit is 0 (modulo 10 congruent to 0), the number is valid !

// Todo
// > Prompt for input
// > Calculate checksum
// > Check for card lenght and starting digits

#include <stdio.h>
#include <cs50.h>

int main()
{
    long ccNumber = 0;  // Creditcard number
    int digit;      // Current digit
    int tempDigit;  // Copy of digit to be altered throught the program
    int digitMultiplied; // Used if the multiplied digit is bigger than 10, need to use the modulo operator to get every digit
    int checksum;   // If == 0, CC is valid, else it is invalid
    int sumA = 0;       // Sum of the multiplied digits
    int sumB = 0;       // Sum of "sumA" + every digit that weren't multiplied
    int count = 0;      // Increase for every digit, needed for later to check if it is a AMEX, MASTERCARD or VISA

    printf("Please enter a credit card number you want to check\n");
    // Get Creditcard Number
    do
    {
        ccNumber = get_long("Number: ");
    }
    while (ccNumber < 1 || ccNumber > 9999999999999999); // Check if CC Number has at most 16 digits

    // Get every digit in ccNumber
    long tempNum = ccNumber;    // Create copy of the CC number, to be altered through the program
    while (tempNum != 0)
    {
        digit = tempNum % 10;
        tempNum = tempNum / 10;
        count++;

        // Check if "count" is even, if "count" is even multiply "digit" by 2, else don't multiply
        if (count % 2 == 0) // Even = multiply digit by 2
        {
            tempDigit = digit * 2;
            if (tempDigit >= 10) // If the multiplied number is bigger than 10 we need to use modulo again to get every digit
            {
                digitMultiplied = tempDigit % 10;
                tempDigit = tempDigit / 10;
                sumA = sumA + digitMultiplied;
            }
            sumA = sumA + tempDigit;
        }
        else    // Odd = dont multiply digit
        {
            sumB = sumB + digit;
        }
    }
    checksum = (sumA + sumB) % 10;
    // Now we need to find the corresponding CC company, which the CC number belongs to
    // AMEX: starts with 34, 37 || 15-digit numbers
    // MASTERCARD: 51,52,53,54,55 || 16-digit numbers
    // VISA: 4 || 13 or 16-digit numbers

    // Get the first to digit of the given CC number
    while (ccNumber >= 100)
    {
        ccNumber = ccNumber / 10;   // Divide by 10 each iteration, not by 100. It is safer with 10.
    }

    // Check to which company the given CC belongs
    if (checksum == 0 && ((count >= 13 && count <= 16) && count != 14))
    {
        if (ccNumber == 34 || ccNumber == 37 || ccNumber == 51 || ccNumber == 52
            || ccNumber == 53 || ccNumber == 54 || ccNumber == 55 || ccNumber / 10 == 4)
        {
            if (count == 15 && (ccNumber == 34 || ccNumber == 37))
            {
                printf("AMEX\n");
            }

            if (count == 16 && (ccNumber == 51 || ccNumber == 52 || ccNumber == 53 || ccNumber == 54 || ccNumber == 55))
            {
                printf("MASTERCARD\n");
            }

            if ((count == 13 || count == 16) && ccNumber / 10 == 4)
            {
                printf("VISA\n");
            }
        }
        else
        {
            // "ccNumber" doesn't start with a corresponding number, so the card is not from AMEX, MASTERCARD or VISA
            printf("INVALID\n");
        }
    }
    else
    {
        // Checksum is not O, so the CC is not valid
        printf("INVALID\n");
    }
}
