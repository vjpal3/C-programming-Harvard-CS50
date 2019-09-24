#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    if (argc == 2) 
    {
        string keyword =  argv[1];
        for (int i = 0; i < strlen(keyword); i++) 
        {
            if (!isalpha(keyword[i])) 
            {
                printf("Usage: ./caesar keyword\n");
                return 1;
            }
        }     
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        int key_counter = 0;
        int special = 0;
        for (int i = 0; i < strlen(plaintext); i++) 
        {
            int key = shift(keyword[key_counter]);
            if (isupper(plaintext[i])) 
            {
                int num = plaintext[i] - 'A';
                printf("%c", (num + key) % 26 + 'A');
                special = 1;
            }
            else if (islower(plaintext[i])) 
            {
                int num = plaintext[i] - 'a';
                printf("%c", (num + key) % 26 + 'a');
                special = 1;
            }
            else 
            {
                printf("%c", plaintext[i]);
                special = 0;
            }
           
            if (special && key_counter < strlen(keyword) - 1) 
            {
                key_counter++;
            }
            else if (special && key_counter == strlen(keyword) - 1)
            {
                key_counter = 0;
            }
        }
        printf("\n");
        return 0;
    }
    else 
    {
        printf("Usage: ./caesar keyword\n");
        return 1;
    }
}

int shift(char c) 
{
    if (isupper(c)) 
    {
        return ((int)(c) - 'A');
    }
    else  
    {
        return ((int)(c) - 'a');
    }
}

