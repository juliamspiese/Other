#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //makes sure user only types one word at command line
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    //assigns keyword to string 'key'
    string key = argv[1];
    //assigns length of keyword to integer 'keylength'
    int keylength = strlen(key);
    //returns invalid response if keyword contains non-alphabetical characters
    for (int i = 0, n = keylength; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int j = 0, k = 0, o = strlen(plain); j < o; j++)
    { 
        int key_index = tolower(key[k % keylength]) - 'a';
        if (isalpha(plain[j]))
        {
            if (isupper(plain[j]))
            {
                printf("%c", ((((plain[j] + key_index) - 'A') % 26) + 'A'));
                k++;
            }    
            else if (islower(plain[j]))
            {
                printf("%c",((((plain[j] + key_index)- 'a') % 26) + 'a'));
                k++;
            }
        }
        else
        {
             printf("%c", plain[j]);
        }
    }    
    printf("\n");
    return 0; 
}
