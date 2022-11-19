#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_key(int argc, char *argv[]);
void caesar_cipher(FILE *plain_text, int key);

int main(int argc, char *argv[])
{
    int key;
    // Let's call the function to check if the input is correct and if the key is valid.
    key = check_key(argc, argv);
    // If the function returns 0 it means that something is wrong with the input, and the program must stop.
    if (key == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // if it's all good with the key, we can ask for the plain text file the user wants to cipher.
    FILE *plain_text;
    char name[50];
    printf("Insert the name of the text file (name.txt): ");
    scanf("%s", name);
    plain_text = fopen(name, "r"); //Open the text file in read mode;
    if (plain_text == NULL)
    {
        printf("The file could not be opened!");
        return 1;
    }

    // Having the key and the plain text we can call the function to cipher the plain text and print the final cipher text.
    caesar_cipher(plain_text, key);
    return 0;
}

int check_key(int argc, char *argv[])
{
    // First let's check if the user wrote two "words" in the input: './caesar x'. Where x is the key.
    if (argc != 2)
    {
        return 0; // indicates that the number of parameters / ''words'' in the input was not correct.
    }
    // Now let's check if the second "word", the key, is a number (function is digit) and if it is > 0 (atoi converts an string into an int).
    int key, tam_key = strlen(argv[1]);
    for (int i = 0; i < tam_key; i++)
    {
        if ((isdigit(argv[1][i]) == 0) || (atoi(argv[1]) <= 0))
        {
            return 0; // indicates that some of the char from the key is not a number or the number informed is <= 0.
        }
    }
    // if it is all good we can return the key (as a digit) to the main function.
    key = atoi(argv[1]);
    return key;
}

void caesar_cipher(FILE *plain_text, int key)
{
    FILE *cipher_text; //Create the output txt file.
    cipher_text = fopen("output.txt", "w"); //Open the text file in read mode;
    if (cipher_text == NULL)
    {
        printf("Problem creating the output file!");
        return;
    }
    char aux;
    fprintf(cipher_text,"%s","ciphertext: ");
    const int correction_factor_upper = 65;
    const int correction_factor_lower = 97;
    const int correction_factor_caesar = 26;
    while(fscanf(plain_text,"%c",&aux) != EOF)
    {
        // first we need to check if the corresponding char in the position i of the string text is a letter.
        if (isalpha(aux))
        {
            // if it is, let's check wether it is upper or lower case, to apply the correct ceasar formula to cipher the letter unsing the key (check .md file)
            if (isupper(aux))
            {
                aux = ((((aux - correction_factor_upper) + key) % correction_factor_caesar) + correction_factor_upper);
                fprintf(cipher_text,"%c", aux);
            }
            else
            {
                aux = ((((aux - correction_factor_lower) + key) % correction_factor_caesar) + correction_factor_lower);
                fprintf(cipher_text,"%c", aux);
            }
        }
        // if it is not a letter, we just print it as it is.
        else
        {
            fprintf(cipher_text,"%c", aux);
        }
    }
    fclose(plain_text);
    fclose(cipher_text);
    printf("\n");
}
