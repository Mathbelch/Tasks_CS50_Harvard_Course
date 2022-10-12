#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_key(int argc, char *argv[]);
void substitution_cipher(char key[], FILE *plain_text);

int main(int argc, char *argv[])
{
    // Let's first call the function to check if the imput is correctly and the key is valid.
    int validation = check_key(argc, argv);
    // If the function doesn't return 1 it means that something is wrong with the input, and the program must stop.
    if (validation != 1)
    {
        return 1;
    }

    //if it's all good with the key, we can ask for the plain text file the user wants to cipher.
    FILE *plain_text;
    char name[50];
    printf("Insert the name of the text file (testx.txt): ");
    scanf("%s", name);
    plain_text = fopen(name, "r"); //Open the text file in read mode;
    if (plain_text == NULL)
    {
        printf("The file could not be opened!");
        return 1;
    }

    // Having the key and the plain text we can call the function to cipher the plain text and print the final cipher text.
    substitution_cipher(argv[1], plain_text);
    return 0;
}

int check_key(int argc, char *argv[])
{
    // First let's check if the user wrote two "words" in the input: ./substitution x. Where X is the alphabetical key.
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 0; // indicates that the number of parameters / ''words'' in the input was not correct.
    }
    // Now let's check if the second "word", the key, contains 26 alphabetical and distinct characteres.
    int tam_key = strlen(argv[1]);
    if (tam_key != 26)
    {
        printf("Key must contain 26 characterers.\n");
        return 0;
    }
    for (int i = 0; i < tam_key; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characterers.\n");
            return 0;
        }
        for (int j = i + 1; j < tam_key; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key should not contain repeated characterers.\n");
                return 0;
            }
        }
        // Since the key is not case sensitive, let's change any upper case letter for its corresponding lower case letter.
        argv[1][i] = tolower(argv[1][i]);
    }
    // if it is all good we can return 1 to the main function.
    return 1;
}

void substitution_cipher(char key[], FILE *plain_text)
{
    //Let's create an index so we can compare positions to help us making the cipher.
    char  alphabetical_index[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    FILE *cipher_text; //Create the output txt file.
    cipher_text = fopen("output.txt", "w"); //Open the text file in read mode;
    if (cipher_text == NULL)
    {
        printf("Problem creating the output file!");
        return;
    }

    fprintf(cipher_text,"%s","ciphertext: ");
    char aux;
    while(fscanf(plain_text,"%c",&aux) != EOF)
    {
            for (int j = 0; j < 26; j++)
            {
                //In case the char in the plain_text is an upper case, we need to ensure the cipher char will be upper as well.
                if (isupper(aux))
                {
                    // If the char in the plain text is the same as the one in alphabetical index [j], we found its substitution char position [j] in the key.
                    if (tolower(aux) == alphabetical_index[j])
                    {
                        aux = toupper(key[j]);
                        break;
                    }
                }
                else
                {
                    if (aux == alphabetical_index[j])
                    {
                        aux = key[j];
                        break;
                    }
                }
            }
    fprintf(cipher_text,"%c", aux);
    }
    fclose(plain_text);
    fclose(cipher_text);
}
