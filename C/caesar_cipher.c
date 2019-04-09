#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{       
    while (argc != 2)
    {
        printf("Usage: ./caesar.key\n");
        return 1;
    }
    const int K = 1;
    for (int i = 0; i < argc; i++)
        {
           for (int j = 0, n = strlen(argv[K]); j < n; j++) 
           {
               if (isdigit(argv[K][j]))
               {
                    int key = atoi(argv[K]);
                    string plain = get_string("plaintext: ");
                    printf("ciphertext: ");
                    for (int l = 0, m = strlen(plain); l < m; l++)
                    {
                        char c = (char) plain[l];
                        if (isupper(c))
                        {
                            printf("%c",(((c - 'A' + key) % 26) + 'A'));
                        }    
                        else if (islower(c))
                        {
                            printf("%c",(((c - 'a' + key) % 26) + 'a'));
                        }
                        else
                        {
                            printf("%c", c);
                        }
                    }
                    printf("\n");
                    return 0; 
               }
               else
               {
                   printf("Usage: ./caesar.key\n");
                   return 1;
               }
            }
        }
}
