#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n1, n2, s1 = 0, s2 = 0, n_dig = 0, curr_dig = 0;
    long init, t, card_num;
    
    do 
    {
        card_num = get_long("Enter Card Number : ");
    }
    while (card_num < 0);
    
    t = card_num;
    
    while (t != 0)
    {
        n1 = t % 10;
        t = t / 10;
        n2 = t % 10;
        t = t / 10;
        n2 = n2 * 2;
        n2 = (n2 / 10) + (n2 % 10);
        s1 = s1 + n1;
        s2 = s2 + n2;    
    }
    
    if ((s1 + s2) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    while (card_num != 0)
    {
        curr_dig = card_num % 10;
        n_dig++;
        
        if (n_dig == 13 && curr_dig == 4)
        {
            printf("VISA\n");
            return 0;            
        }
        else if ((n_dig == 14) && (card_num == 34 || card_num == 37))
        {
            printf("AMEX\n");
            return 0;
        }
        else if ((n_dig == 15) && (card_num >= 51 && card_num <= 55))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if (n_dig == 16 && curr_dig == 4)
        {
            printf("VISA\n");
            return 0;
        }
        
        card_num = card_num / 10;
    }
    
    printf("INVALID\n");
    return 0;
}
