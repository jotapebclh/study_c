#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Loop of lines by height (range: 1 - 8)
    for (int row = 1; row <= height; row++)
    {
        // Displays the required spaces as follows:
        // Supposing height = 3
        // ..# -> Row 1 - 2 Spaces
        // .## -> Row 2 - 1 Space
        // ### -> Row 3 - 0 Spaces
        // Spaces will always be the height value minus the current row
        for (int k = 1; k <= height - row; k++)
        {
            printf(" ");
        }

        // Displays a # based on the current row
        for (int j = 1; j <= row; j++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}

