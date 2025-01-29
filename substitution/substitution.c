#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_duplicate(char *str);
char *rotate(char *key, char *plaintext);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        for (int i = 1; argv[1][i] != '\0'; i++)
        {
            if (!isalpha(argv[1][i]) || strlen(argv[1]) != 26 || has_duplicate(argv[1]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    char key[27];
    strcpy(key, argv[1]);
    char plaintext[500];
    char ciphertext[500];

    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    strcpy(ciphertext, rotate(key, plaintext));
    printf("ciphertext: %s", ciphertext);
}

char *rotate(char *key, char *plaintext)
{
    static char ciphertext[500];

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[plaintext[i] - 'A']);
            }
            else
            {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    return ciphertext;
}

int has_duplicate(char *str)
{
    int letras[26] = {0};

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
        {
            int index = tolower(str[i]) - 'a';
            if (letras[index] > 0)
            {
                return 1;
            }
            letras[index]++;
        }
    }
    return 0;
}
