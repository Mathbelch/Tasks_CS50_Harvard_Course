#include <stdio.h>
#include <ctype.h>
#include <string.h>

// First let's fix the maximum number of voters and candidates in this election.
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// Now let's declare the preferences[i][j] array, where i is represents the voter and j represent their each preferences.
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// The best way to track the candidates is using a struct having their names, votes counter and an eliminated status flag.
typedef struct
{
    char name[50];
    int votes;
    int eliminated;
}
candidate;

// Array of candidates structs
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates are constant during the program.
int voter_count;
int candidate_count;

// Function prototypes:
int vote(int voter, int rank, char name[]);
void tabulate(void);
int print_winner(void);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    // Check for invalid usage of command line arguments
    if (argc < 2)
    {
        printf("Usage: ./nameFile [candidate ...]\n");
        return 1;
    }

    // Determining the number of candidates:
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES) // Here we must check if the number of candidates is less than the maximum established.
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    /* If it's all good with the command line arguments, let's populate the candidates array with their names, votes (0) and
    the flag F, since nobody has been eliminated yet*/
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name,argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    //Let's ask for the number of voters and check if it is inside the limit established before.
    printf("Insert the number of voters: ");
    scanf("%d",&voter_count);
    if (voter_count > MAX_VOTERS || isdigit(voter_count) != 0 || (voter_count <= 0))
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // i represents the number of the voter, j represents the preferences of each 'i' voter.
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            // Record vote, unless it's invalid (in case there's no candidate with the name given).
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Now the preferences are all recorded, we must keep holding runoffs until there's a winner or a tie:
    int loop = 1;
    while (loop == 1)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        int won = print_winner();
        if (won)
        {
            loop = 0;
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        int tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("\n\nAnd there is a TIE with...");
                    printf("%s\n", candidates[i].name);
                }
            }
            loop = 0;
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid and return true. Otherwise just return false and do not change anything.
int vote(int voter, int rank, char name[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return 1;
        }
    }
    return 0;
}

// Tabulate votes for non-eliminated candidates (using the flag).
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes ++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one.
int print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count * 0.5)
        {
            printf("\n\nAnd the winner is...");
            printf("%s\n", candidates[i].name);
            return 1;
        }
    }
    return 0;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS; // If we set min as max. voters, any other number will be the 'new' min.
    for (int i = 0; i < candidate_count; i++)
    {
        if ((min > candidates[i].votes) && (!candidates[i].eliminated))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise.
int is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        /*since we've already checked there's no winner and the minimum vote, to see if there's a tie we just need to check if all the candidates have the
        minimum vote number or not, considering only the non eliminated ones*/
        if ((candidates[i].votes != min) && (!candidates[i].eliminated))
        {
            return 0;
        }
    }
    return 1;
}

// Eliminate the candidate (or candidates) in last place (with the minimum number of votes)
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }
    return;
}
