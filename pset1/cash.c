#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int cents, n = 0;
    do{
        change = get_float("Enter Change : ");
    }
    while(change<0.0);
    
    cents = round(change*100);
    
    
    n += cents / 25; 
    +((cents%25)/10)+(((cents%25)%10)/5)+(((cents%25)%10)%5); 
    cents = cents % 25;
    n += cents / 10;
    cents = cents % 10;
    n += cents / 5;
    cents = cents 5 
    
    printf("%d\n", n);
}

