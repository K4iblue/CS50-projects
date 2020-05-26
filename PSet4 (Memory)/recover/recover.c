#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// JPEG first 3 bytes pattern:
// 0xff 0xd8 0xff

// Fourth byte is one of these
// 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef
// So the first four bits of the fourth byte will always be "1110"

// TODO
// 1. Open "Memory Card"
// 2. Look for beginning of a JPEG
// 3. Open a new JPEG file, that we write you
// 4. Write 512 byte until a new JPEG is found
// 5. Stop at end of file

int main(int argc, char *argv[])
{
    // Check if we have atleast one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover 'filename'\n");
        return 1;
    }

    // Open file that was given by the user
    FILE *fp = fopen(argv[1], "r");

    // Check if the file was opened successfully, else return 1
    if (fp == NULL)
    {
        printf("Error: Cant open file\n");
        return 1;
    }

    // Variables
    BYTE buffer[512];           // Buffer where we store a 512 byte sized "block"
    char filename[8];           // Array for storing the filename of the current JPEG
    int counter = 0;            // Counter for increasing filenumbers
    bool new_jpg = false;       // Boolean so that we can check if we found a new JPEG
    FILE *img = NULL;           // Temporary file, we write the JPEG to

    // While loop as long we are not at the end of the file
    while ((fread(buffer, 512, 1, fp)) == 1)
    {
        // If start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If we found a new JPEG file, we need to close the old one
            if (new_jpg == true)
            {
                // Close the last file, so that we can open a new one
                fclose(img);
            }
            // If it is the first JPEG file on the memory card, we set the boolean to true
            else
            {
                new_jpg = true;
            }

            // Open a new JPEG with the right filename
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        if (new_jpg == true)
        {
            // Write blocks into a file
            fwrite(buffer, 512, 1, img);
        }
    }

    // Close all open files
    fclose(img);
    fclose(fp);
}