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
    RGBTRIPLE rev[height][width];
    // iterate with the image pixels starting with the a row then its respective columns:
    for (int i = 0; i < height; i++)
    {
        // start with the edges:
        rev[i][0].rgbtRed = image[i][width - 1].rgbtRed;
        rev[i][0].rgbtGreen = image[i][width - 1].rgbtGreen;
        rev[i][0].rgbtBlue = image[i][width - 1].rgbtBlue;

        rev[i][width - 1].rgbtRed = image[i][0].rgbtRed;
        rev[i][width - 1].rgbtGreen = image[i][0].rgbtGreen;
        rev[i][width - 1].rgbtBlue = image[i][0].rgbtBlue;
        // copy the rows as reversed:
        for (int j = 1; j < width; j++)
        {
            rev[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            rev[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            rev[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
        }

        // assign the reversed pixels to the original image:
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = rev[i][k].rgbtRed;
            image[i][k].rgbtGreen = rev[i][k].rgbtGreen;
            image[i][k].rgbtBlue = rev[i][k].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width]; // temporary RGBTRIPLE holder
    // iterate with the image pixels starting with the a row then its respective columns:
    for (int i = 0; i < height; i++)
    {
        // top row pixels:
        if (i == 0)
        {
            for (int j = 0; j < width; j++)
            {
                // leftmost column:
                if (j == 0)
                {

                    image[i][j].rgbtRed;
                    image[i][j].rgbtGreen;
                    image[i][j].rgbtBlue;
                }
                // middle columns:
                else if (j != width - 1)
                {
                }
                // rightmost column:
                else
                {
                }
            }
        }
        // middle rows pixels:
        else if (i != height - 1)
        {
        }
        // bottom row pixels:
        else
        {
        }
    }

    // assign the blurred pixels to the original image:
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = tmp[x][y].rgbtRed;
            image[x][y].rgbtGreen = tmp[x][y].rgbtGreen;
            image[x][y].rgbtBlue = tmp[x][y].rgbtBlue;
        }
    }
    return;
}

// 3hrs + and counting: 14 July 2021