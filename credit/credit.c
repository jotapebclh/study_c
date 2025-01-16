#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isValid(const char *number);
void printCardBrand(const char *number);
int calculateSum(const char *number);

int main(void)
{
    // Array to store the card number
    char cardNumber[20];

    do
    {
        printf("Number: ");
        scanf("%19s", cardNumber); // Read up to 19 characters
    }
    while (cardNumber < 0);

    if (isValid(cardNumber))
    {
        printCardBrand(cardNumber);
    }
    else
    {
        printf("INVALID\n");
    }
}

int isValid(const char *cardNumber)
{
    int length = strlen(cardNumber);
    
    // Return true if lenght is valid and checksum passes
    return (length == 13 || length == 15 || length == 16) && calculateSum(cardNumber);
}

int calculateSum(const char *cardNumber)
{
    int sum = 0; // Accumulated sum
    int is_second = 0; // Flag to alternate between digits
    size_t length = strlen(cardNumber); // Get the length

    // Iterate through the card number from the end
    for (int i = length - 1; i >= 0; i--)
    {
        if (!isdigit(cardNumber[i]))
        {
            return 0; // Return false if non-numeric characters are found
        }

        int digit = cardNumber[i] - '0'; //  Convert character to integer

        if (is_second) // Double the digit on alternate positions
        {
            digit *= 2;
            if (digit > 9) // Subtract 9 if the digit exceeds 9
            {
                digit -= 9;
            }
        }

        sum += digit; // Add the digit to the total sum
        is_second = !is_second; // Toggle the flag
    }

    return (sum % 10) == 0; // Return true if the sum is divisible by 10
}

void printCardBrand(const char *cardNumber)
{
    size_t length = strlen(cardNumber);

    if ((strncmp(cardNumber, "34", 2) == 0 || strncmp(cardNumber, "37", 2) == 0) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((strncmp(cardNumber, "51", 2) == 0 || strncmp(cardNumber, "52", 2) == 0 ||
              strncmp(cardNumber, "53", 2) == 0 || strncmp(cardNumber, "54", 2) == 0 ||
              strncmp(cardNumber, "55", 2) == 0) &&
             length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((cardNumber[0] == '4') && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

