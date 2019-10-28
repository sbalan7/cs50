#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift (char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else 
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if(!isalpha(argv[1][i]))
            {
                printf("Usage: ./vigenere keyword\n");
            }
        }
    }
    
    string keyword = argv[1];
    
    string message = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(message); i++)
    {
        int key = shift(keyword[i%strlen(keyword)]);
        
        if (!isalpha(message[i]))
        {
            printf("%c", message[i]);
            continue;
        }
        
        if (islower(message[i]))
        {
            message[i] = (((message[i]-97)+key)%26)+97;
            printf("%c", message[i]);
        }
        
        if (isupper(message[i]))
        {
            message[i] = (((message[i]-65)+key)%26)+65;
            printf("%c", message[i]);
        }        
    }
    
    printf("\n");
    return 0;
}

int shift (char c)
{
    return (toupper(c)-65);
}
