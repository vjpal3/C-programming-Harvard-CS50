#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2) 
    {
        string str_key =  argv[1];
        for (int i = 0; i < strlen(str_key); i++) 
        {
            // Check if the key is numeric          
            if (!isdigit(str_key[i])) 
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        //  Convert the key into integer
        int key = atoi(str_key);
        // Get the plain-text from the user:
        string plaintext = get_string("plaintext: ");

        printf("ciphertext: ");
        // Encipher the the alphabets preserving their case
        for (int i = 0; i < strlen(plaintext); i++) 
        {
            if (isupper(plaintext[i])) 
            {
                int num = plaintext[i] - 'A';
                // Wrap around the alphabets between a-z or A-Z 
                printf("%c", (num + key) % 26 + 'A');
            }
            else if (islower(plaintext[i])) 
            {
                int num = plaintext[i] - 'a';
                printf("%c", (num + key) % 26 + 'a');
            }
            else 
            {
                // characters that aren’t alphabetical should remain unchanged
                printf("%c", plaintext[i]);
            }        
        }
        printf("\n");
        return 0;
    }
    else 
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
