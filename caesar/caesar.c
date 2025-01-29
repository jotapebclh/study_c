#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int only_digits(const char *str);
char *rotate(int key, char *plaintext);

int main(int argc, char *argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int k = atoi(argv[1]);
    char plaintext[500];
    char ciphertext[500];

    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    strcpy(ciphertext, rotate(k, plaintext));
    printf("ciphertext: %s", ciphertext);
}

char *rotate(int key, char *plaintext)
{
    static char ciphertext[500];

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                plaintext[i] = plaintext[i] - 'A';
                ciphertext[i] = ((plaintext[i] + key) % 26) + 'A';
            }
            else
            {
                plaintext[i] = plaintext[i] - 'a';
                ciphertext[i] = ((plaintext[i] + key) % 26) + 'a';
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    return ciphertext;
}

int only_digits(const char *str)
{
    int i = 0;

    int has_digit = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
        has_digit = 1;
        i++;
    }
    return has_digit;
}
