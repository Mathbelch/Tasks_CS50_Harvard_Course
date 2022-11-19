#include <stdio.h>
#include <locale.h>

int ask_value (void);
void build_pyramid(int n);

int main(void)
{
    printf("Mario pyramid: \n");
    int high = ask_value();
    printf("\n");
    build_pyramid(high);
    printf("\n");
    return 0;
}

int ask_value()
{
    int high;
    do
    {
        printf("Insert pyramid high (1 to 8): ");
        scanf("%d",&high);
    }
    while ((high < 1) || (high > 8));
    return high;
}

void build_pyramid(int n)
{
for (int i = 0; i < n ; i++) // line control
    {
        for (int j = 0; j < n ; j++)     // first pyramid
        {
            if (i + j >= n -1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf ("  ");                  // separating colummns
        for (int j = 0; j < n; j++)   // second pyramid
        {
            if (i >= j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
    printf ("\n");
    }
}
