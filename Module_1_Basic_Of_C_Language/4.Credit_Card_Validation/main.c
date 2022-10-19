#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Luhn_Algorithm(int number[], int size);
void search_flag(int first, int second, int aux);

int main(void)
{
    char number[20]; //Let's first put the card number into an array of char (string), to avoid dealing with too large number.
    printf("Card validation.\n\nInsert the card number (just numbers): ");
    fflush(stdin);
    scanf("%s", number);
    int size = strlen(number); //Checking and recording the size (number of digits)of the card.
    int numberVet[size]; // Now we can copy each digit from the card number individually to an array of int.
    for (int i = 0; i < size; i++)
    {
        numberVet[i] = number[i] - '0'; // number is an array of char, so we must subtract '0' (ASCII) to save it as an int.
    }
    Luhn_Algorithm(numberVet, size);
    return 0;
}

void Luhn_Algorithm(int number[], int size)
{
    int sum1 = 0; //This will record the sum of the digits multiplied by two (starting from the one in the penultimate position, always jumping one position).
    int sum2 = 0; //This will record the sum of the digits that are not multiplied by two (starting from the one in the last position, always jumping one position).
    int sum = 0; //This will be the final sum of Luhn's Algorithm
    int i = size - 2;
    while(i >= 0)
    {
        int aux;
        aux = (number[i] * 2);
        if(aux < 10)
        {
            sum1 += aux;
        }
        else
        {
            sum1 = sum1 + 1 + (aux % 10);
        }
        i-=2;
    }
    int j = size - 1;
    while (j >= 0)
    {
        sum2 += number[j];
        j-=2;
    }
    sum = sum1 + sum2;

    if(sum % 10 == 0) //If the last digit of the sum is zero, the card is valid and we can call the search_flag function.
    {
        printf("\nValid card!\n...flag: ");
        search_flag(number[0], number[1], size);
    }
    else
    {
        printf("INVALID\n");
    }
}

void search_flag(int first, int second, int aux)
{
    //For discovering the flag we must check the first digits and also the total number of digits.
    if (first == 3 && (second == 4 || second == 7) && (aux == 15))
    {
        printf("AMEX\n");
    }
    else if (first == 5 && (second > 0 && second < 6) && (aux = 16))
    {
        printf("MASTERCARD\n");
    }
    else if (first == 4 && (aux == 16 || aux == 13))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
