#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    FILE *text; //Making a pointer for a text file;
    char name[50];
    printf("Insert the name of the text file (name.txt): ");
    scanf("%s", name);
    text = fopen(name, "r"); //Open the text file in read mode;
    if (text == NULL)
    {
        printf("The file could not be opened!");
        return 1;
    }

    int number_letters = 0, number_words = 0, number_sentences = 0, cl_index = -1;
    float letter_per_100_words, sentences_per_100_words;
    // Let's obtain the parameters needed with some functions of ctype library and also a simple comparison.
    char aux;
    while(fscanf(text,"%c",&aux) != EOF)
    {
        if (isalpha(aux))
        {
            number_letters++;
        }
        else if (isspace(aux))
        {
            number_words++;
        }
        else if ((aux == '.') || (aux == '!') || (aux == '?'))
        {
            number_sentences++;
        }
    }
    fclose(text);

    // Here we need to make a correction in the 'number_words' parameter. We can't declare it as 1 in case of no words typed.
    if (number_words > 0)
    {
        number_words++;
    }
    printf("\n Letters = %d  , Sent = %d  , words = %d\n", number_letters, number_sentences, number_words);

    // Now let's calculate the Coleman-Liau Index.
    letter_per_100_words = ((number_letters * 100.0) / number_words);
    sentences_per_100_words = ((number_sentences * 100.0) / number_words);
    cl_index = round(((0.0588 * letter_per_100_words) - (0.296 * sentences_per_100_words) - 15.8));
    printf("\n L = %f  , S = %f  , Index = %d\n", letter_per_100_words, sentences_per_100_words, cl_index);

    // Now lets give the result:
    if (cl_index == -1)
    {
        printf("\nERROR\n");
        return 1;
    }
    else if (cl_index <= 1)
    {
        printf("\nBefore Grade 1\n");
    }
    else if (cl_index >= 16)
    {
        printf("\nGrade 16+\n");
    }
    else
    {
        printf("\nGrade %d\n", cl_index);
    }
    return 0;
}
