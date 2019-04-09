#include <cs50.h>
#include <stdio.h>
#include <math.h>

int cointracker(void);

int main(void)
{
    //sort change into n coins
    int coins = cointracker();
    //print number of coins used
    printf("%i\n", coins);
}

// while n-cent coin can be used, increase count by number of coins used, decrease change by n*count

int cointracker(void)
{
    //make receive float
    float  f;
    do
    {
        f = get_float("Change: ");
    }    
    while (f == false || f <= 0);
    //convert to cents
    int change = round(f * 100);
    //coin count variable
    int coins = 0;
    int coinarray[4] = {25, 10, 5, 1};
    for( int i = 0; i < 4; i++)
    {   
        int n = coinarray[i];
        while (change >= n)
        {   
            change -= n;       
            coins += 1;
        }
    }
    return coins;
}

