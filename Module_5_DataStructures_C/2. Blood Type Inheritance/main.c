// Simulate genetic inheritance of blood type.

#include <stdio.h>
#include <stdlib.h> // for using rand(), srand(), malloc()
#include <time.h> // for using time()

// Each person has two parents and two alleles.
typedef struct person
{
    //Each value points to one of the parents (other 'person' structures).
    struct person *parents[2];
    char alleles[2];
}
person;

// Let's define the number of generations to predict and the ident lenght (just to print the results correctly).
const int GENERATIONS = 5;
const int INDENT_LENGTH = 4;

// Functions prototypes:
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator to be used in the 'random_allele' function.
    srand(time(0));

    // Create a new family with the number of generations defined before.
    person *p = create_family(GENERATIONS);
    if (p == NULL)
    {
        return 1;
    }

    // Print family tree of blood types.
    print_family(p, 0);

    // Free all memory used dinamically.
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO - 1: Allocate memory for new person:
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }

    // Generation with parent data.
    if (generations > 1)
    {
        // TODO - 2: Recursively create blood type histories for parents:
        person *pFirst = create_family(generations - 1);
        person *pSecond = create_family(generations - 1);

        p->parents[0] = pFirst;
        p->parents[1] = pSecond;

        // TODO - 3: Randomly assign child alleles based on parents:

        p->alleles[0] = pFirst->alleles[(rand() % 2)];
        p->alleles[1] = pSecond->alleles[(rand() % 2)];
    }

    // Generation without parent data.
    else
    {
        // TODO - 4: Set parent pointers to NULL and randomly assign alleles:
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // TODO - 5: Return newly created person:
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO - 6: Handle base case:
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents and child:
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    free(p);

}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

