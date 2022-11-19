#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int checkingJPG(BYTE *buffer);

int main(int argc, char *argv[])
{
    // First we must check the command line argument (memory card name) and also if the file was oppened correctly.
    if (argc != 2)
    {
        printf("Usage: ./recovery image\n");
        return 1;
    }
    FILE *MemoryCard = fopen(argv[1], "r");
    if (MemoryCard == NULL)
    {
        printf("Image could not be oppened\n");
        return 1;
    }

    // Now it is necessary to read the file from its begining, saving blocks of 512 bytes into a buffer pointer:
    int jpgCounter = 0;
    int tamBuffer; // If it's less than 255 it means we reached the end of the memory card file.
    FILE *img = NULL;
    char filename[8];
    do
    {
        BYTE *buffer = calloc(512, sizeof(BYTE));
        tamBuffer = fread(buffer, sizeof(BYTE), 512, MemoryCard);
        if(checkingJPG (buffer) == 1)// Starts of a jpg file.
        {
            if (jpgCounter == 0) // For the first jpg found:
            {
                sprintf(filename, "%03i.jpg", jpgCounter);
                img = fopen(filename,"w");
                fwrite(buffer, sizeof(BYTE), 512, img);
                jpgCounter++;
                free(buffer);
            }
            else // If it is not the first jpg:
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpgCounter);
                img = fopen(filename,"w");
                fwrite(buffer, sizeof(BYTE), 512, img);
                jpgCounter++;
                free(buffer);
            }
        }
        else // It can be a continuation of a jpg or memory garbage:
        {
            if (jpgCounter == 0) // So it's memory garbage
            {
                free(buffer);
            }
            else if (jpgCounter > 0)// It's part of the previously jpg.
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
                free(buffer);
            }
        }
    }
    while(tamBuffer == 512);
    fclose(img);
    fclose(MemoryCard);
}

int checkingJPG(BYTE *buffer)
{
    if (buffer[0] == 255)
    {
        if (buffer[1] == 216)
        {
            if (buffer[2] == 255)
            {
                if ((buffer[3]& 0xf0) == 224)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}