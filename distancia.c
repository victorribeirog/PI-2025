#include <stdio.h>

int nc = 10;
int nl = 10;

int img[] = {
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,0,0,0,
    0,0,1,1,1,1,0,0,0,0,
    0,0,1,1,1,1,1,0,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,
    0,0,0,0,0,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0
    
};

void showImage (int img[]){
    for (int i = 0; i < nl; i++){
        for (int j = 0; j < nc; j++)
            printf("%3d ", img[i*nc + j]); //mat[i][j]
        printf("\n");
    }
}

int menor(int x, int y, int z){
    if (x < y && x < z)
        return x;
    else
        if ( y < z)
            return y;
        else
            return z;

}

void distance (int img[]){
    for (int i = 1; i < nl; i++){
        for (int j = 1; j < nc; j++)
        {
            int a = (i - 1) * nc + j;
            int b = i * nc + j - 1;
            int p = i * nc + j;
            if(img[p] !=0){
                if(img[a] + 1 < img[b] + 1)
                    img[p] = img[a] + 1;
                else
                    img[p] = img[b] + 1;
            }
        }
    }
    for (int i = nl-2; i >= 0; i--){
        for (int j = nc-2; j >= 0; j--)
        {
            int p = i * nc + j;
            int a = i * nc + j + 1;
            int b = (i + 1) * nc + j;
            img[p] = menor(img[p],img[a] + 1, img[b] + 1);
        }
    }
}

int main () {
    showImage(img);
    puts("");
    distance(img);
    showImage(img);
}