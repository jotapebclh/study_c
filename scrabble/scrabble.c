#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char word[100]);

int main(void)
{
    char word_player_1[100];
    char word_player_2[100];

    printf("Player 1: ");
    fgets(word_player_1, sizeof(word_player_1), stdin);

    printf("Player 2: ");
    fgets(word_player_2, sizeof(word_player_2), stdin);

    int score1 = compute_score(word_player_1);
    int score2 = compute_score(word_player_2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(char word[100])
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {

        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}
