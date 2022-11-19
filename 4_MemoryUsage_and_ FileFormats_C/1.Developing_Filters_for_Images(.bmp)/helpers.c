#include "helpers.h"
#include <math.h>

typedef struct
{
    double blue;
    double green;
    double red;
} sum;

typedef struct
{
    double blue;
    double green;
    double red;
} avg;

/* Convert image to grayscale maintainning the intensity of the colour (first we must check the average of each RGB value
and set all the RGB of the pixel to this avg value)*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double avg = 0;
            int sum = 0;
            sum = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed);
            avg = (double) sum / 3;
            image[h][w].rgbtBlue = round(avg);
            image[h][w].rgbtGreen = round(avg);
            image[h][w].rgbtRed = round(avg);
        }
    }
    return;
}

// Reflect image horizontally (we must swap opposite sized pixels of a column - inverting them, repeating the process for all columns)
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        int width_Counter = width - 1;
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE aux = image[h][w];
            image[h][w] = image[h][width_Counter];
            image[h][width_Counter] = aux;
            width_Counter--;
        }
    }
    return;
}

// Blur image using BloxBlur code.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Lets make a copy of the image array:
    RGBTRIPLE original[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }

    // Now we can make the maths using the original and modify the image:
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sum sum_squares;
            sum_squares.blue = 0;
            sum_squares.green = 0;
            sum_squares.red = 0;
            avg avg_squares;
            int counter = 0;
            // For each pixel we must check the quadrant values of RGB:
            for (int h2 = h - 1; h2 <= h + 1; h2++)
            {
                if (h2 >= 0 && h2 < height)
                {
                    for (int w2 = w - 1; w2 <= w + 1; w2++)
                    {
                        if (w2 >= 0 && w2 < width)
                        {
                        sum_squares.blue += original[h2][w2].rgbtBlue;
                        sum_squares.green += original[h2][w2].rgbtGreen;
                        sum_squares.red += original[h2][w2].rgbtRed;
                        counter++;
                        }
                    }
                }
            }
                // Now we set the average value of RGB quadrant and then set this value into the image's pixel.
                avg_squares.blue = (double) sum_squares.blue / counter;
                avg_squares.green = (double) sum_squares.green / counter;
                avg_squares.red = (double) sum_squares.red / counter;
                image[h][w].rgbtBlue = round(avg_squares.blue);
                image[h][w].rgbtGreen = round(avg_squares.green);
                image[h][w].rgbtRed = round(avg_squares.red);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Let's define Gx and Gy, that will help finding the edges in x and y directions of each pixel.
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    // Lets make a copy of the image array:
    RGBTRIPLE original[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }

    // Now we can look at the original image and set Gx and Gy for each color of a particular pixel in original[h][w]:
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Inside a particular pixel, we must check the 3x3 squad it belongs. First let declare the variables that can help:
           sum sum_squares_X, sum_squares_Y; // These structures sum will keep the values of Gx and Gy for each pixel's colour.
           sum_squares_X.blue = 0;
           sum_squares_Y.blue = 0;
           sum_squares_X.green = 0;
           sum_squares_Y.green = 0;
           sum_squares_X.red = 0;
           sum_squares_Y.red = 0;
           int Gx_w_counter, Gy_w_counter;
           int Gx_h_counter = 0, Gy_h_counter = 0;
           sum result;
           // For each pixel we must check the quadrant values of RGB:
           for (int h2 = h - 1; h2 <= h + 1; h2++)
           {
                Gx_w_counter = 0;
                Gy_w_counter = 0;
                if (h2 >= 0 && h2 < height)
                {
                    for (int w2 = w - 1; w2 <= w + 1; w2++)
                    {
                        if (w2 >= 0 && w2 < width)
                        {
                            sum_squares_X.blue += (original[h2][w2].rgbtBlue) * (Gx[Gx_h_counter][Gx_w_counter]);
                            sum_squares_X.green += (original[h2][w2].rgbtGreen) * (Gx[Gx_h_counter][Gx_w_counter]);
                            sum_squares_X.red += (original[h2][w2].rgbtRed) * (Gx[Gx_h_counter][Gx_w_counter]);
                            sum_squares_Y.blue += (original[h2][w2].rgbtBlue) * (Gy[Gy_h_counter][Gy_w_counter]);
                            sum_squares_Y.green += (original[h2][w2].rgbtGreen) * (Gy[Gy_h_counter][Gy_w_counter]);
                            sum_squares_Y.red += (original[h2][w2].rgbtRed) * (Gy[Gy_h_counter][Gy_w_counter]);
                            Gx_w_counter++;
                            Gy_w_counter++;
                        }
                        else
                        {
                            Gx_w_counter++;
                            Gy_w_counter++;
                        }
                    }
                    Gx_h_counter++;
                    Gy_h_counter++;
                }
                else
                {
                    Gx_h_counter++;
                    Gy_h_counter++;
                }
            }
            // With all Gx and Gy values set, we must pow them to turn any negative number into positive, sum and finally take the square root:
            result.blue = sqrt(pow(sum_squares_X.blue,2) + pow(sum_squares_Y.blue,2));
            result.green = sqrt(pow(sum_squares_X.green,2) + pow(sum_squares_Y.green,2));
            result.red = sqrt(pow(sum_squares_X.red,2) + pow(sum_squares_Y.red,2));

            // Before setting the image's pixel to its new values, we must consider that the maximum possible value for each colour is 255.
            if (round(result.blue) > 255)
            image[h][w].rgbtBlue = 255;
            else
            image[h][w].rgbtBlue = round(result.blue);

            if (round(result.green) > 255)
            image[h][w].rgbtGreen = 255;
            else
            image[h][w].rgbtGreen = round(result.green);

            if (round(result.red) > 255)
            image[h][w].rgbtRed = 255;
            else
            image[h][w].rgbtRed = round(result.red);
        }
    }
    return;
}

// Sepia filter
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float sepiaGreen, sepiaBlue, sepiaRed;
            sepiaBlue = (0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) + (0.131 * image[h][w].rgbtBlue);
            sepiaGreen = (0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) + (0.168 * image[h][w].rgbtBlue);
            sepiaRed = (0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) + (0.189 * image[h][w].rgbtBlue);

            if (sepiaBlue > 255)
            image[h][w].rgbtBlue = 255;
            else if (sepiaBlue < 0)
            image[h][w].rgbtBlue = 0;
            else
            image[h][w].rgbtBlue = round(sepiaBlue);

            if (sepiaGreen > 255)
            image[h][w].rgbtGreen = 255;
            else if (sepiaGreen < 0)
            image[h][w].rgbtGreen = 0;
            else
            image[h][w].rgbtGreen = round(sepiaGreen);

            if (sepiaRed > 255)
            image[h][w].rgbtRed = 255;
            else if (sepiaRed < 0)
            image[h][w].rgbtRed = 0;
            else
            image[h][w].rgbtRed = round(sepiaRed);
        }
    }
    return;
}