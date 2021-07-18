#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
BYTE e = 0xe0;
BYTE f = 0xff;
BYTE g = 0xd8;

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

    BYTE *buffer = malloc(sizeof(BYTE));
    int n = fread(buffer, sizeof(BYTE), 1, input);
    printf("The 0e = %u and 0f = %u\n", e, f);

    fclose(input);
    free(buffer);
}

// 1.5+ hrs 18 July 2021