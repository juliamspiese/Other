#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(string prompt);
void pyramid(int n);

int main(void)
{
    int i = get_pyramid_height("Height: ");
    pyramid(i);
}

int get_pyramid_height(string prompt)
{
    int n;
    do
    {
       n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}

void pyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            for (int k = n - 1; k >= i && j == true; k--)
            {
                printf(" ");
            }
            printf("#");
        }
        printf("\n");
    }
}
