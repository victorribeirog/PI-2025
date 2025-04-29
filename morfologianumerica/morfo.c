/*-------------------------------------------------------------------------
 * Morfologia Numérica
 * Por Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../utils/imagelib.h"

image dilata(image img)
{
    int h = img->nr; //altura
    int w = img->nc; // largura
    image Out = img_clone(img);
    int mn = img->ml; //maximo nivel de cinza
    int *pixels = img->px; // vetor de pixels
    for (int i = 1; i < h - 1; i++)
        for (int j = 1; j < w - 1; j++)
        {
            int max = -1;
            for (int x = -1; x <= 1; x++)
                for (int y = -1; y <= 1; y++)
                {
                    int px = pixels[(i + x) * w + j + y];
                    if (px > max)
                        max = px;
                }
            Out->px[i * w + j] = max;
        }
    return Out;
}

image erode(image img)
{
    int h = img->nr; //altura
    int w = img->nc; // largura
    image Out = img_clone(img);
    int mn = img->ml; //maximo nivel de cinza
    int *pixels = img->px; // vetor de pixels
    for (int i = 1; i < h - 1; i++)
        for (int j = 1; j < w - 1; j++)
        {
            int min = mn + 1;
            for (int x = -1; x <= 1; x++)
                for (int y = -1; y <= 1; y++)
                {
                    int px = pixels[(i + x) * w + j + y];
                    if (px < min)
                        min = px;
                }
            Out->px[i * w + j] = min;
        }
    return Out;
}

image gradient(image img)
{
    int h = img->nr; //altura
    int w = img->nc; // largura
    image Out = img_clone(img);
    int mn = img->ml; //maximo nivel de cinza
    int *pixels = img->px; // vetor de pixels
    for (int i = 1; i < h - 1; i++)
        for (int j = 1; j < w - 1; j++)
        {
            int min = mn + 1;
            int max = -1;
            for (int x = -1; x <= 1; x++)
                for (int y = -1; y <= 1; y++)
                {
                    int px = pixels[(i + x) * w + j + y];
                    if (px < min)
                        min = px;
                    if (px > max)
                        max = px;
                }
            Out->px[i * w + j] = max - min;
        }
    return Out;
}

void msg(char *s)
{
    printf("\nErosao/Dilatacao");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
    printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    char nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, GRAY, GRAY);

    //-- read image
    In = img_get(nameIn, GRAY);
    //-- transformation
    Out = gradient(In);
    //-- save image
    img_put(Out, nameOut, GRAY);

    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
