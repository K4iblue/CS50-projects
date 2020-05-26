#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    
    // Define height, by asking the user
    while (height < 1 || height > 8)
    {
        height = get_int("How tall should the pyramid be? (Choose a number between 1 and 8)\n");
    }

    // Printing pyramid
    for (int i = 0; i < height; i++) // Printing a new line
    {
        for (int k = height - 1; k > i; k--) // Printing dots / spaces
        {
            printf(" ");
        }

        for (int j = -1; j < i; j++)  // Printing hashes
        {

            printf("#");
        }
        printf("\n");
    }

}
