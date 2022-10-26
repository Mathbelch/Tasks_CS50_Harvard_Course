#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Maximum number of candidates as a constant.
#define MAX 9
//Maximum number of char in a candidate's name.
#define NAME 50

// Candidates have name and vote count.
typedef struct
{
    char name[NAME];
    int votes;
}
candidate;

// Declaring an array of candidates structures with maximum of MAX (in this case, nine) candidates.
candidate candidates[MAX];

// Number of candidates (It's okay to declare it as a Global Variable since we're using this through all code.
int candidate_count;

// Function prototypes:
int vote(char name[]);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage: we must type ./fileName candidates' names (at least 2 and max of MAX -> 9)
    if (argc < 2)
    {
        printf("Usage: ./nameFile [candidate ...]\n");
        return 1;
    }

    // Let's now count how many candidates were included in the election:
    candidate_count = argc - 1;

    // Let's check if the candidates number is higher than the maximum allowed.
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    /* If everything is okay with the prompt input, lets allocate the candidates on their respectively
    positions in the structure array, with their names and their initial vote number equal 0.*/
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name,argv[i + 1]);
        candidates[i].votes = 0;
    }

    //We must ask the user for how many votes they want to register.
    int voter_count;
    printf("\nInsert the number of voters: ");
    scanf("%d", &voter_count);
    if (((isdigit(voter_count) != 0) || (voter_count <= 0))) // Here I check if the informed value is a positive number.
    {
        printf("\nIncorrect number of voters!\n");
        return 1;
    }

    // Loop over all voters asking the candidate's name and executing the VOTE function for each:
    for (int i = 0; i < voter_count; i++)
    {
        char name[NAME];
        printf("Vote: ");
        scanf("%s", name);

        // Check for invalid vote (if the name informed is not on the list, we should give a warning and don't consider the vote)
        if (!vote(name)) //Function vote will return false if that happens, if the vote is valid, we just count the vote.
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner(s) of election using the print_winner function.
    print_winner();
}

/* Function to update candidate votes for each new vote given (return true) and also check if the name
typed is not on the list (returning false). */
int vote(char name[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    return 0;
}

// Function to compare the vote number and print the winner (or winners) of the election
void print_winner(void)
{
    int winner_flag = 0; // Let's keep the winner's position, instead of its name.
    // Here let's fix a first winner.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > candidates[winner_flag].votes)
        {
            winner_flag = i;
        }
    }

    // Now let's print the winner name and check if there are other winners.
    printf("\n\nAnd the winner is...");
    printf("%s\n", candidates[winner_flag].name);

    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == candidates[winner_flag].votes) && (i != winner_flag))
        {
            printf("\n\nAnd there is a TIE with...");
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
