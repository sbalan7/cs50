#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    BYTE chunk[512];
    int nImgs = 0;

    char filename[8];
    FILE *outptr = NULL;

    while (true)
    {
        // read a block of the memory card image
        size_t bytesRead = fread(chunk, sizeof(BYTE), 512, inptr);

        if (bytesRead == 0 && feof(inptr))
            break;

        bool jpgHeader = (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff && (chunk[3] & 0xf0) == 0xe0);

        if (jpgHeader && outptr != NULL)
        {
            fclose(outptr);
            nImgs++;
        }

        if (jpgHeader)
        {
            sprintf(filename, "%03i.jpg", nImgs);
            outptr = fopen(filename, "w");
        }

        if (outptr != NULL)
            fwrite(chunk, sizeof(BYTE), bytesRead, outptr);
    }


    fclose(outptr);
    fclose(inptr);

    return 0;
}
