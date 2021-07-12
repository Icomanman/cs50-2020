#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Modifies the volume of an audio file
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t *bytes = malloc(sizeof(uint8_t));
    // Copy header from input file to output file one at a time via a for loop:
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fread(bytes, sizeof(uint8_t), 1, input);
        fwrite(bytes, sizeof(uint8_t), 1, output);
    }

    int16_t *buffer = malloc(sizeof(int16_t));
    // Read samples from input file and write updated data to output file
    while (fread(buffer, sizeof(int16_t), 1, input))
    {
        // scale the samples:
        *buffer *= factor;
        fwrite(buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
    // free the memory taken by malloc:
    free(bytes);
    free(buffer);
    return 0;
}

// 2hrs: 12 Jul 2021