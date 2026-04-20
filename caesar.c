#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool only_digits(string s);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    // Ensure correct usage
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate that the argument is all digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert key to integer
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Print ciphertext label
    printf("ciphertext: ");

    // Loop through each character of plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        char encrypted = rotate(c, key);
        printf("%c", encrypted);
    }

    // Print newline at end
    printf("\n");
    return 0;
}

// Check if string contains only digits
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Rotate character by key positions
char rotate(char c, int key)
{
    if (isupper(c))
    {
        return ((c - 'A' + key) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + key) % 26) + 'a';
    }
    else
    {
        return c;
    }
}
