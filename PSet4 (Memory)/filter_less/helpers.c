#include "helpers.h"
#include <math.h>

// Convert image to grayscale (black and white version of the image)
// Loop over the 2d-array
// Calculate the average pixel value of every pixel (average of RGB)
// If needed round the average, because we need an integer
// Set each color value to the average value
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over height
    for (int i = 0; i < height; i++)
    {
        // Loop over width
        for (int j = 0; j < width; j++)
        {
            float average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
// Loop over 2d-array
// Calculate RGB values with the sepia algorithm given by the CS50 Staff
// If needed round each RGB value, because we need an integer
// If a RGB value is over 255, we set it to 255, because the range is 0-255
// Given algorithms:
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over height
    for (int i = 0; i < height; i++)
    {
        // Loop over width
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Red value
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Green value
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Blue value
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
// Loop over 2d-array
// Swap pixel on horizontally opposite sides
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary array for storing values
    int temp[3];

    // Loop over heigth
    for (int i = 0; i < height; i++)
    {
        // Loop over width
        for (int j = 0; j < width / 2; j++)
        {
            // Temporary store RGB value of the current pixel
            temp[0] = image[i][j].rgbtRed;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtBlue;

            // Write the corresponding pixel on the horizontally opposite side into the current pixel
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            // Write pixel saved in temp to the position of the corresponding pixel on the horizontally opposite side
            image[i][width - j - 1].rgbtRed = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtBlue = temp[2];
        }
    }
    return;
}

// Blur image
// We are using a boxed blur
// We need to calculate the average of the RGB values of the neighbour pixels
// Then we set the RGB of the current pixels to the calculated averages
// Loop over 2d-array
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables we need for calculating the averages
    int avgBlue;
    int avgGreen;
    int avgRed;
    float counter;

    // Array for temporary saving
    RGBTRIPLE temp[height][width];

    // Loop over height
    for (int h = 0; h < height; h++)
    {
        // Loop over width
        for (int w = 0; w < width; w++)
        {
            // "Reset" our variables
            avgBlue = 0;
            avgGreen = 0;
            avgRed = 0;
            counter = 0.00;

            // Now we need to loop over the neighbour pixels
            for (int i = -1; i < 2; i++)
            {
                // Check if neighbour pixel exists (height)
                if (h + i < 0 || h + i > height - 1)
                {
                    continue;
                }

                // Check if neighbour pixel exists (width)
                for (int j = -1; j < 2; j++)
                {
                    if (w + j < 0 || w + j > width - 1)
                    {
                        continue;
                    }

                    // Calculate the average RGB values of the neighbour pixels
                    avgBlue += image[h + i][w + j].rgbtBlue;
                    avgGreen += image[h + i][w + j].rgbtGreen;
                    avgRed += image[h + i][w + j].rgbtRed;
                    
                    // Increase counter if pixel exist, so we can later average the RGB values
                    counter++;
                }
            }
            temp[h][w].rgbtBlue = round(avgBlue / counter);
            temp[h][w].rgbtGreen = round(avgGreen / counter);
            temp[h][w].rgbtRed = round(avgRed / counter);
        }
    }

    // Finally we copy the RGB values from the temporary array into the real image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }
    return;
}