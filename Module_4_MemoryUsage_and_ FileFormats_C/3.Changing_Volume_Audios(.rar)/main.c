// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void copyHeader(FILE *input, FILE *output);
void changeSamples(FILE *input, FILE *output);

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
float factor;

int main(void)
{
    FILE *input; //Making a pointer for the input audio file;
    char name[50];
    printf("Insert the name of the input file (name.wav): ");
    scanf("%s", name);
    input = fopen(name, "r"); //Open the input file in read mode;
    if (input == NULL)
    {
        printf("The input file could not be opened!");
        return 1;
    }

    FILE *output; //Making a pointer for the output file;
    char name2[50];
    printf("Insert the name of the output file (name.wav): ");
    scanf("%s", name2);
    output = fopen(name2, "w"); //Open the output file in write mode;
    if (output == NULL)
    {
        printf("The output file could not be opened!");
        return 1;
    }
    // Open files and determine scaling factor:

    printf("Insert the changing factor: ");
    scanf("%f", &factor);

    // Copy header from input file to output file:
    copyHeader(input, output);

    // Read samples from input file and write updated data to output file
    changeSamples(input, output);

    // Close files
    fclose(input);
    fclose(output);
}

void copyHeader(FILE *input, FILE *output)
{
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
}

void changeSamples(FILE *input, FILE *output)
{
    int counter = 1;
    while (counter == 1)
    {
        int16_t buffer; // We must use a buffer to store and manipulate data between the input and the output file.
        counter = fread(&buffer, sizeof(int16_t), 1, input); //copy the value from input file to the buffer.
        if (counter == 1)
        {
            buffer = buffer * factor; //Manipulate it in the buffer.
            fwrite(&buffer, sizeof(int16_t), 1, output); //Copy from the buffer to the output file.
        }
    }
}