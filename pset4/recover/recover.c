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

    int n = 0;
    int count = 0;
    char filename[8]; // to hold the filename, say, 0001.jpg\0
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    do
    {
        // read 512 bytes at a time
        n = fread(buffer, sizeof(BYTE), 512, input);
        if (buffer[0] == f && buffer[1] == g && buffer[2] == f && (buffer[3] & 0xf0) == e)
        {
            // set the filenames
            if (count < 10)
            {
                sprintf(filename, "00%i.jpg", count);
            }
            else if (count > 10 && count < 100)
            {
                sprintf(filename, "0%i.jpg", count);
            }

            FILE *out = fopen(filename, "w");
            // printf("buffer[0] = %u, buffer[1] = %u, buffer[2] = %u, buffer[3] = %u\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            fwrite(buffer, sizeof(BYTE), 512, out);
            fclose(out);
            count += 1;
        }
    } while (n != 0);

    // printf("Total Count: %i\n", count);
    fclose(input);
    free(buffer);
}
// 3+ hrs 18 July 2021