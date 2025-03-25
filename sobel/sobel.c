/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Processing of the image negative
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(__WIN64__) || defined(__CYGWIN__)
#include "..\\utils\\imagelib.h"
#elif defined(__linux__)
#include "../utils/imagelib.h"
#endif
int abs(int n)
{
    return n < 0 ? -n : n;
}

image sobel(image img)
{
    image out = img_clone(img);
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;

    for (int i = 0; i < h; i++)
    {
        out->px[i * w] = 0;
        out->px[i * w + w - 1] = 0;
    }
    for (int j = 0; j < w; j++)
    {
        out->px[j] = 0;
        out->px[(h - 1) * w + j] = 0;
    }
    for (int i = 1; i < h - 1; i++)
        for (int j = 0; j < w - 1; j++)
        {
            int soma, Z[9];
            int k = 0;
            for (int y = -1; y < 2; y++)
                for (int x = -1; x < 2; x++)
                    Z[k++] = pixels[(i + y) * w + (j + x)];
            soma = abs((Z[6] + 2 * Z[7] + Z[8]) - (Z[0] + 2 * Z[1] + Z[2])) +
                   abs((Z[2] + 2 * Z[5] + Z[8]) - (Z[0] + 2 * Z[3] + Z[6]));
            out->px[i * w + j] = soma > max ? 0 : 255;
        }
    return out;
}

void msg(char *s)
{
    printf("\nSobel image");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  image-name[.pgm]\n\n", s);
    printf("    image-name[.pgm] is image file in pgm format \n\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    //-- define input/output file name
    img_name(argv[1], nameIn, nameOut, GRAY, GRAY);

    //-- read image
    In = img_get(nameIn, GRAY);
    //-- transformation
    Out = sobel(In);
    //-- save image
    img_put(Out, nameOut, GRAY);

    //-- show image
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    puts(cmd);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
