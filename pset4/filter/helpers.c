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
    /* Classify pixels before row iterations: 
    top corners/row (interior columns), 
    middle rows edges/interior columns and
    bottom corners/row (interior columns) 
    then make vertical "steps" to consider top and bottom pixels from a given row
    (from left-to-right iteration) */
    for (int i = 0; i < height; i++)
    {
        // top row:
        if (i == 0)
        {
            for (int j = 0; j < width; j++)
            {
                // top-left corner:
                if (j == 0)
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 2 steps of 2 horizontal blocks to get 4 pixels:
                    for (int k = i; k < 2; k++)
                    {
                        sum_red += image[i + k][j].rgbtRed + image[i + k][j + 1].rgbtRed;
                        sum_green += image[i + k][j].rgbtGreen + image[i + k][j + 1].rgbtGreen;
                        sum_blue += image[i + k][j].rgbtBlue + image[i + k][j + 1].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 4.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 4.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 4.0);
                }
                // interior columns:
                else if (j != width - 1)
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 2 steps of 3 horizontal blocks to get 6 pixels:
                    for (int k = i; k < 3; k++)
                    {
                        sum_red += image[i + k][j - 1].rgbtRed + image[i + k][j].rgbtRed + image[i + k][j + 1].rgbtRed;
                        sum_green += image[i + k][j - 1].rgbtGreen + image[i + k][j].rgbtGreen + image[i + k][j + 1].rgbtGreen;
                        sum_blue += image[i + k][j - 1].rgbtBlue + image[i + k][j].rgbtBlue + image[i + k][j + 1].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 6.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 6.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 6.0);
                }
                // top-right:
                else
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 2 steps of 2 horizontal blocks to get 4 pixels:
                    for (int k = i; k < 2; k++)
                    {
                        sum_red += image[i + k][j - 1].rgbtRed + image[i + k][j].rgbtRed;
                        sum_green += image[i + k][j - 1].rgbtGreen + image[i + k][j].rgbtGreen;
                        sum_blue += image[i + k][j - 1].rgbtBlue + image[i + k][j].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 4.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 4.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 4.0);
                }
            }
        }
        // middle rows pixels:
        else if (i != height - 1)
        {
            for (int j = 0; j < width; j++)
            {
                // leftmost column:
                if (j == 0)
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 3 steps of 2 horizontal blocks to get 6 pixels:
                    for (int k = i; k < 3; k++)
                    {
                        sum_red += image[i + k][j].rgbtRed + image[i + k][j + 1].rgbtRed;
                        sum_green += image[i + k][j].rgbtGreen + image[i + k][j + 1].rgbtGreen;
                        sum_blue += image[i + k][j].rgbtBlue + image[i + k][j + 1].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 4.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 4.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 4.0);
                }
                // middle columns:
                else if (j != width - 1)
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 2 steps of 3s to make 6 blocks of pixels:
                    for (int k = i; k < 3; k++)
                    {
                        sum_red += image[i + k][j - 1].rgbtRed + image[i + k][j].rgbtRed + image[i + k][j + 1].rgbtRed;
                        sum_green += image[i + k][j - 1].rgbtGreen + image[i + k][j].rgbtGreen + image[i + k][j + 1].rgbtGreen;
                        sum_blue += image[i + k][j - 1].rgbtBlue + image[i + k][j].rgbtBlue + image[i + k][j + 1].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 6.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 6.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 6.0);
                }
                // rightmost column:
                else
                {
                    int sum_red = 0;
                    int sum_green = 0;
                    int sum_blue = 0;
                    // 2 steps of 2s to make 4 blocks of pixels:
                    for (int k = i; k < 2; k++)
                    {
                        sum_red += image[i + k][j - 1].rgbtRed + image[i + k][j].rgbtRed;
                        sum_green += image[i + k][j - 1].rgbtGreen + image[i + k][j].rgbtGreen;
                        sum_blue += image[i + k][j - 1].rgbtBlue + image[i + k][j].rgbtBlue;
                    }

                    // assign the values:
                    tmp[i][j].rgbtRed = rond(sum_red / 4.0);
                    tmp[i][j].rgbtGreen = rond(sum_green / 4.0);
                    tmp[i][j].rgbtBlue = rond(sum_blue / 4.0);
                }
            }
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