#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int initial_population = 0;
    int final_population = 0;
    do
    {
        printf("Insert the initial_population: ");
        scanf("%d",&initial_population);
    }
    while(initial_population < 9); // According to the restrictions.
    do
    {
        printf("Insert the final_population: ");
        scanf("%d",&final_population);
    }
    while(final_population < initial_population); // The final population can't be smaller nor equal the initial one, otherwise would make no sense to calculate it.
    fflush(stdin);
    int years = 0;
    while(initial_population < final_population)   // When the population reaches the final value chosen by the user, the simulation must stop.
    {
        initial_population = (initial_population + (initial_population/ 3) - (initial_population / 4)) ; // Growth rate of these specie per year..
        years++;
    }
    printf("Years: %d\n", years);
    return 0;
}
