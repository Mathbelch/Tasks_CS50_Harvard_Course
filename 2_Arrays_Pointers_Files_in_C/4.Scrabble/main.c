#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Points assigned to each letter of the alphabet according to Scrabble table:
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char  alphabetical_index[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


int* startGame (int *numberPlayers);
int compute_score(char word[]);
void check_printWinner (int *totalPlayers, int *score);
void printScores (int *totalPlayers, int *scores);

int main(void)
{
    int option;
    int numberPlayers;
    int *score = NULL; // This is a pointer that will point to the memory address of a future list of scores from each player in the round.

    // Initializing the first round:
    score = startGame(&numberPlayers);
    // Check and print the winner
    check_printWinner (&numberPlayers, score);
    int turned = 1; //This will keep the game turned on. If users choose to turn it off, then we change to 0.
    while(turned == 1)
    {
        // Menu:
        fflush(stdin);
        printf("\nType 1 to see all the players scores\nType 2 to start a new round\nType 3 to finish application\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printScores(&numberPlayers, score);
            break;
        case 2:
            free(score);
            score = startGame(&numberPlayers);
            check_printWinner (&numberPlayers, score);
            break;
        case 3:
            free(score);
            printf("\n\n..............Thank you for playing with Scrabble!");
            return 0;
        }
    }
}

int* startGame (int *numberPlayers)
{

    char word[50];
    int *score = NULL;
    int flagOK;
    do
    {
        fflush(stdin); // To clean the keyboard memory in order to avoid entering in an infinitive loop.
        printf("\nWelcome to Scrabble:\nHow many players (maximum of 9) will play this game?\n");
        scanf("%d", numberPlayers);
        if (*numberPlayers <= 0 || *numberPlayers > 9)
        {
            printf("\n******Incorrect number of players!\n");
        }
        else
        {
            flagOK = 1;
        }

        } while (flagOK != 1);

    //Let's allocate the list of scores dynamically, in case we need to change the number of players.
    //calloc (stdlib.h) will allocate and also set the values (scores of each player) to 0.
    score = calloc(*numberPlayers, sizeof(int));
    if (score == NULL)
    {
        return NULL;
    }

    // Get input words from players and score its points into the score list.
    printf("\n........... TYPE YOUR WORDS ...........\n");
    for (int i = 0; i < *numberPlayers; i++)
    {
        printf("Insert the word of player %d: ", i+1);
        scanf("%s", word);
        score[i] = compute_score(word);
    }
    return score;
}

int compute_score(char word[])
{
    // Compute and return score for string:
    int size = strlen(word);
    int size_alf = strlen(alphabetical_index);
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        //Only alphabetical characteres count points on scrabble, so let's check it first;
        if (isalpha(word[i]))
        {
            //If there's a letter, we can now check its value on scrabble table (using the index to find the point position)
            for (int j = 0; j < size_alf; j++)
            {
                if (tolower(word[i]) == alphabetical_index[j])
                {
                    counter += POINTS[j];
                    break;
                }
            }
        }
    }
    return counter;
}

void check_printWinner (int *totalPlayers, int *score)
{
    int winnerScore = 0;
    int winnerPosition = 0;
    int flagTie = 1; // if 1, it means there is a tie!
    for (int i = 0; i < *totalPlayers; i++)
    {
        if (winnerScore < score[i])
        {
            winnerScore = score[i];
            winnerPosition = i;
            flagTie = 0;
        }
        else if (winnerScore > score[i])
        {
            flagTie = 0;
        }
        else
        {
            flagTie = 1;
        }

    }
    if (flagTie == 1)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("\n.............Player %i wins with %i points!\n", winnerPosition + 1, winnerScore);
    }
}

void printScores (int *totalPlayers, int *score)
{
    printf("\n......... SCORES .........\n");
    for (int i = 0; i < *totalPlayers; i++)
    {
        printf("Player %i: %i points!\n", i + 1, score[i]);
    }
}
