#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // If more than one command-line-argument is found else return 1
    if (argc == 2  && isdigit(*argv[1]))
    {

        // Check if a command-line-argument is found else return 1
        int len = strlen(argv[1]);
        for (int n = 0; n < len; n++)
        {
            // Check if the command-line-argument is all digitss
            if (isdigit(argv[1][n]) == false)
            {
                return 1;
            }
        }

        // Transform the "key" (which is simply = argv) to an integer
        int key = atoi(argv[1]);

        // If the command-line-argument is an negative-integer, return 1
        if (key < 0)
        {
            printf("Test: %d\n", key);
            return 1;
        }

        string plaintext = get_string("plaintext:");
        printf("ciphertext:");

        // Loop to tranform the plainttext into ciphertext
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", ((plaintext[i] + key) - 65) % 26 + 65);
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", ((plaintext[i] + key) - 97) % 26 + 97);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}