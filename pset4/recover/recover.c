#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Unable to open file.\n");
    }

    uint8_t *buffer = malloc(sizeof(uint8_t));
    int n = fread(buffer, sizeof(uint8_t), 1, input);
    printf("The %i byte is %u\n", n, *buffer);

    fclose(input);
    free(buffer);
}

// 1+ hrs 18 July 2021