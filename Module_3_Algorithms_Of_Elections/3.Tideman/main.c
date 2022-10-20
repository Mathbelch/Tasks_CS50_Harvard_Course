#include <unistd.h> //So we can use the sleep function, allowing to see the final result when the code is executed from cmd on windows.
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// For convenience let's set the max number of candidates as a constant.
#define MAX 9

// Preferences[i][j] is an 2-D array representing the number of voters who prefer candidate i over candidate j (their margin).
int preferences[MAX][MAX];

// This 2-D array (adjacency matrix) can represent the candidate's graph, where locked[i][j] = 1 (true) means i is locked in over j (see function lock_pairs).
int locked[MAX][MAX];

// Each pair may have a winner and a loser, so let's save their positions in a struct called pair.
typedef struct
{
    int winner;
    int loser;
}
pair;

// Let's implement an array of candidates, saving their names (j) and thus using their position (i) on this array as a code to other functions.
char candidates[MAX][50];
// This array of the struct pairs allows us to save the positions of all winners and looser for each pair where there is a winner and a looser.
pair pairs[MAX * (MAX - 1) / 2];

//Global variables
int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int cycled(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage of the command line arguments.
    if (argc < 2)
    {
        printf("Usage: ./nameFile [candidate ...]\n");
        sleep(5);
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        sleep(5);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // The position of each candidate in the candidate's array will be the order it was previously declared in the command line argument.
        strcpy(candidates[i],argv[i + 1]);
    }

    // Clear graph of locked in pairs, setting all values as false.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }

    // Clear the preference array, setting all values as zero.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("\nInsert the number of voters: ");
    scanf("%d",&voter_count);
    if (isdigit(voter_count) != 0 || (voter_count <= 0)) //checking if the value informed is a correct number > 0.
    {
        printf("Incorrect number of voters\n");
        sleep(5);
        return 3;
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Declaring the array ranks[i], which represents the voter's (i) preferences in order (j), re-declared for each new voter.
        int ranks[candidate_count];

        // Query for each rank:
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                sleep(5);
                return 3;
            }
        }
        printf("\n");
        /* After all preferences of the voter has been validated by the 'vote' function, we can finally record its preferences on the:
        global variable preferences[][], called once for each voter*/
        record_preferences(ranks);
    }

    // We can now call a set of functions to end up our algorithm and print the winner:
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    sleep(5);
    return 0;
}

// Update ranks given a new vote, returning true if it is done well and false if there is no matching name in the candidate's list.
int vote(int rank, char name[], int ranks[])
{
    // Let's check the name given in the candidate's array and, if there is a match we save the position of the candidate in ranks[rank] = ranks[j] in main.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return 1;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks:
void record_preferences(int ranks[])
{
    //ranks[i] will always be the position of the candidate prefered over the one in ranks[j], since ranks is ordered by preferences.
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other on the pair's array of struct:
void add_pairs(void)
{
    /* Here we must think about the preferences[i][j] array, and check the pair of candidates individually. That means we must
    check how many voters prefer candidate i over j (preferences[i][j]) and also how many prefer j over i (preferences[j][i]).
    This function will then save the positions of the winner and loosers for each pair on the pars array of struct.*/
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

/* Let's use an inverted Bubble Sort to sort pairs in decreasing order by strength of victory, checking the margin of distance
between the votes from winners and loosers of each pair, that means, their victory force (number of winner's votes).*/
void sort_pairs(void)
{

    for (int j = 0; j < pair_count; j++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            // We must look to the preferences array to see how many points the winner has over the loser -> preference[i][j].
            if ((preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser]))
            {
                pair aux = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = aux;
            }
        }
    }
    return;
}

/* This function will check if adding an arrow to the graph would or not create a cycle (two possible situations). */
int cycled(int winner, int loser)
{
    /* In case the winner candidate has already had an arrow pointed to it, from the looser candidate */
    if (locked[loser][winner] == 1)
    {
        return 1;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        /* In case the loser already points an arrow to someone and the winner also points an arrow to this
        same candidate. */
        if (locked[loser][i] == 1 && cycled(winner, i))
        {
            return 0;
        }
    }

    return 0;
}

/* This function must update the Locked 2-D array in order to create the locked graph. For this we set the edges (by setting
true in the array locked[i][j], meaning a locked arrow from i to j is 'drawn' on the graph) in decreasing order of victory
strength, as long as that doesn't create a cycle (what will be checked by a true value returned from the function cycled.).*/
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!cycled(winner, loser))
        {
            locked[winner][loser] = 1;
        }
    }
    return;
}


// Printing the winner of the election: the winner is the candidate who is the source of the graph (does not receive any arrow).
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int flag_source_found = 1;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1) // Means candidate j points an arrow to candidate i, so candidate i is not the source.
            {
                flag_source_found = 0;
                break;
            }
        }
        if (flag_source_found) // Once we found the source, we can see the result.
        {
            printf("\n\nAnd the winner is...");
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
