#include "helpers.h"

int R, G, B;
int oR, oG, oB;
const int POS = 1000;

// name rond to avoid conflict with C's round
int rond(float n)
{
    // truncate the float and round off to the nearest POS:
    int trunc = n * POS;
    int rem = trunc % POS;
    if (rem > 499)
    {
        trunc = ((trunc - rem) / POS) + 1;
    }
    else
    {
        trunc = ((trunc - rem) / POS);
    }
    return trunc;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate with the image pixels starting with the a row then its respective columns:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            R = image[i][j].rgbtRed;
            G = image[i][j].rgbtGreen;
            B = image[i][j].rgbtBlue;

            int avg = rond((R + G + B) / 3.0);

            // assign the values:
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate with the image pixels starting with the a row then its respective columns:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oR = image[i][j].rgbtRed;
            oG = image[i][j].rgbtGreen;
            oB = image[i][j].rgbtBlue;

            R = rond(.393 * oR + .769 * oG + .189 * oB);
            G = rond(.349 * oR + .686 * oG + .168 * oB);
            B = rond(.272 * oR + .534 * oG + .131 * oB);

            R = R > 255 ? 255 : R;
            G = G > 255 ? 255 : G;
            B = B > 255 ? 255 : B;
            // assign the values:
            image[i][j].rgbtRed = R;
            image[i][j].rgbtGreen = G;
            image[i][j].rgbtBlue = B;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// 1.5hrs + and counting: 13 July 2021