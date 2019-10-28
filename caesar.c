#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int shift = atoi(argv[1]) % 26;
    string plain = get_string("plaintext : ");
    
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(plain); i++)
    {
        if (!isalpha(plain[i]))
        {
            printf("%c", plain[i]);
            continue;
        }
        
        if (islower(plain[i]))
        {
            plain[i] = (((plain[i]-97)+shift)%26)+97;
            printf("%c", plain[i]);
        }
        
        if (isupper(plain[i]))
        {
            plain[i] = (((plain[i]-65)+shift)%26)+65;
            printf("%c", plain[i]);
        }
        
    }
    
    printf("\n");
    return 0;
}
