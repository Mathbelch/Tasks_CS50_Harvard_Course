#include <stdio.h>
#include <math.h> // for using round function.

float askForChangeValue(void);
int convert_real_to_cents(float real);
int count_coins(int remaining);

int main(void)
{
    float value_in_real = askForChangeValue();
    int value_in_cents = convert_real_to_cents(value_in_real);
    int amountCoins = count_coins(value_in_cents);
    printf("\nAmount of coins = %d.\n", amountCoins);
    return 0;
}

float askForChangeValue(void)
{
    float value;
    do
    {
        fflush (stdin);
        printf("Insert the change amount you need to give to the client: R$ ");
        scanf("%f",&value);
    }
    while (value <= 0);    // case the informed value is not valid (negative, letters, ...), the program must repeat the message;
    return value;
}

int convert_real_to_cents(float real)
{
    int cents = round(real * 100);       // The round function will convert the float value to an int value.
    return cents;
}

int count_coins(int remaining)
{
    int total_amount = 0;
    while (remaining >= 25)      // Using the ambitious algorithm technique let's move from the biggest to the smallest coin.
    {
        int qtd_25 = remaining / 25;
        remaining -= (qtd_25 * 25);
        total_amount += qtd_25;
    }
    while (remaining >= 10)
    {
        int qtd_10 = remaining / 10;
        remaining -= (qtd_10 * 10);
        total_amount += qtd_10;
    }
    while (remaining >= 5)
    {
        int qtd_5 = remaining / 5;
        remaining -= (qtd_5 * 5);
        total_amount += qtd_5;
    }
    while (remaining >= 1)
    {
        int qtd_1 = remaining / 1;
        remaining -= (qtd_1 * 1);
        total_amount += qtd_1;
    }
    return total_amount;
}
