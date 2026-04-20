#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert key to integer
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Iterate over each character
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            // Shift uppercase letters
            printf("%c", ((c - 'A' + key) % 26) + 'A');
        }
        else if (islower(c))
        {
            // Shift lowercase letters
            printf("%c", ((c - 'a' + key) % 26) + 'a');
        }
        else
        {
            // Leave non-alphabetical characters unchanged
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}
