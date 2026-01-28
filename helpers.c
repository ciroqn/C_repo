#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Follow algorithm for sepia
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // If sums above exceed max hexa value, cap at max value (255), otherwise
            // set as above sum
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the rows
    for (int i = 0; i < height; i++)
    {
        // Loop [through the pixels] within the rows
        for (int j = 0; j < width; j++)
        {
            // if the width (or elements in the row) is odd and the incrementing index
            // equals the decrementing index, break from loop. If even and incrementing index
            // exceeds halfway point, break also
            if ((width % 2 != 0 && j == width - j - 1) || (width % 2 == 0 && j >= round(width/2)))
            {
                break;
            }
            // If above NOT satisfied, swap one end of the row with the corresponding element on
            // the other half
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the rows
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        // Loop [through the pixels] within the rows
        for (int j = 0; j < width; j++)
        {
            double red = 0;
            double green = 0;
            double blue = 0;
            int num_npixels = 0;

            // Loop so that for every pixel we can
            // determine the available pixels to average

            // Treat each pixel as if it's in a 3x3 array (with it being in the 'middle')
            for (int h = i - 1; h <= i + 1; h++)
            {
                for (int w = j - 1; w <= j + 1; w++)
                {
                    // Now test if ith and jth position exist
                    // i.e. if pixel is an 'edge' or 'corner' pixel
                    if ((h >= 0 && h < height) && (w >= 0 && w < width))
                    {
                        // set the RGB values of [i][j]th pixel to the RGB
                        // values of surrounding pixels
                        red += image[h][w].rgbtRed;
                        green += image[h][w].rgbtGreen;
                        blue += image[h][w].rgbtBlue;
                        num_npixels++;
                    }
                }
            }

            // Set copied pixel to be the average of the surrounding pixels
            copy[i][j].rgbtRed = round(red/num_npixels);
            copy[i][j].rgbtGreen = round(green/num_npixels);
            copy[i][j].rgbtBlue = round(blue/num_npixels);

        }
    }

    // Set the actual pixels in the image to be the blurred pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
}
