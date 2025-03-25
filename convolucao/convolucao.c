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

image conv(image img)
{
    image out = img_clone(img);
    int w = img->nc;
    int h = img->nr;
    int max = img->ml;
    int *pixels = img->px;
    int mask[3][3] =
        {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1};
    int a = 3;
    for (int i = a; i < h - a + 1; i++)
        for (int j = a; j < w - a + 1; j++)
        {
            int soma = 0;
            for (int y = -a; y < a + 1; y++)
                for (int x = -a; x < a + 1; x++)
                    soma += pixels[(i + y) * w + (j + x)];
            out->px[i * w + j] = soma / ((2 * a + 1) * (2 * a + 1));
        }
    return out;
}

void msg(char *s)
{
    printf("\nConvolution image");
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
    Out = conv(In);
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
