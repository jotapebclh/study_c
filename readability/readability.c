#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int count_letters(char text[500]);
int count_words(char text[500]);
int count_sentences(char text[500]);
float calculate_grade(int total_letters, int total_words, int total_sentences);

int main(void)
{

    // Grade X
    // If grade is 16 or higher -> Grade 16+
    // If grade is less than 1 -> Before Grade 1

    // Formula: index = 0.0588 * L - 0.296 * S - 15.8
    // L = average number of letters per 100 words in the text
    // S = average number of setences per 100 words in the text

    // Calcular o número de letras no texto, desconsiderar espaços
    // Calcular o número de palavras no texto, separando pelos espaços
    // Calcular o número de sentenças no texto, separando por caracteres como: . ? !

    float grade;
    char text[500];

    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int total_letters = count_letters(text);
    // printf("%i\n", total_letters);

    int total_words = count_words(text);
    // printf("%i\n", total_words);

    int total_sentences = count_sentences(text);
    // printf("%i\n", total_sentences);

    grade = calculate_grade(total_letters, total_words, total_sentences);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
}

int count_letters(char text[500])
{
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_words(char text[500])
{
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' || (i > 0 && text[i - 1] != ' ' && text[i] == '\n'))
        {
            count++;
        }
    }

    return count;
}

int count_sentences(char text[500])
{
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}

float calculate_grade(int total_letters, int total_words, int total_sentences)
{
    float l, s, grade;

    l = (float) total_letters / total_words * 100;
    // printf("l %.2f\n", l);
    s = (float) total_sentences / total_words * 100;
    // printf("s %.2f\n", s);
    grade = round(0.0588 * l - 0.296 * s - 15.8);
    // printf("grade %.2f\n", grade);

    return grade;
}
