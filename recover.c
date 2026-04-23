#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a byte as an 8-bit unsigned integer
typedef uint8_t BYTE;

// Size of a block on the memory card
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the forensic image file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    // Buffer to store a block of data
    BYTE buffer[BLOCK_SIZE];

    // Variables to track image count and files
    int image_count = 0;
    FILE *img_ptr = NULL;
    char filename[8]; // Enough for "xxx.jpg\0"

    // Read through the raw_file 512 bytes at a time
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check if the block starts with a JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If we already have a file open, close it
            if (img_ptr != NULL)
            {
                fclose(img_ptr);
            }

            // Create a new filename (e.g., 000.jpg, 001.jpg)
            sprintf(filename, "%03i.jpg", image_count);

            // Open a new file for writing
            img_ptr = fopen(filename, "w");
            image_count++;
        }

        // If a JPEG file is currently open, write the block to it
        if (img_ptr != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img_ptr);
        }
    }

    // Close any remaining open files
    if (img_ptr != NULL)
    {
        fclose(img_ptr);
    }

    fclose(raw_file);

    return 0;
}
