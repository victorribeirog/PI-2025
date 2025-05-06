#include <stdio.h>

int main(){
    unsigned int px = 0x008B96E0;
    int R, G, B;
    // printf ("%X\n", px & 0xFF);
    R = (px >> 16) & 0xFF;
    G = (px >> 8) & 0xFF;
    B = px & 0xFF;
    printf("R = %d G = %d, B = %d\n", R, G, B);
}