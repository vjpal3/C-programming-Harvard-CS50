#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{
    float change_owed;
    do 
    {
        change_owed = get_float("Change owed: ");
    } 
    while (change_owed < 0);
    
    int cents = round(change_owed * 100);
    int coins[4] = { 25, 10, 5, 1 };
    
    int minimum_coins = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (cents == coins[i]) 
        {
            minimum_coins += 1 ;
            break;
        }
        else if (cents > coins[i])
        {
            int division = cents / coins[i];
            minimum_coins += (division) > 0 ? division : 0;
            cents = cents % coins[i];
        }
    }   
    printf("%i\n", minimum_coins);
}
    
