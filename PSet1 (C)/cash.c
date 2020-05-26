#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // US Coins
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    int coins = 0;
    float change = 0.0;

    change = get_float("Change owed: \n");  //Ask user, how much change is owed
    int ch_round = round(change * 100);

    while (change <= 0) // Check if user input is valid
    {    
        change = get_float("Change owed: \n");
    }

    // Check how many Coins we need
    for (int i = ch_round; i >= quarter; i = (i - quarter)) // Check how many quarters we can use
    {
        ch_round = ch_round - quarter;
        coins++;
    }

    for (int i = ch_round; i >= dime; i = (i - dime))    // Check how many dimes we can use
    {
        ch_round = ch_round - dime;
        coins++;
    }

    for (int i = ch_round; i >= nickel; i = (i - nickel))    // Check how many nickels we can use
    {
        ch_round = ch_round - nickel;
        coins++;
    }

    for (int i = ch_round; i >= penny; i = (i - penny))  // Check how many pennys we can use
    {
        ch_round = ch_round - penny;
        coins++;
    }
    printf("%d\n", coins);
}
