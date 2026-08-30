#include <stdio.h>
#include "mandelbrot.h"

int mandelbrot_point(double re, double im, int max_inter){
    double zre = 0.0;
    double zim = 0.0;

    for (int i =0; i< max_inter; i++){
        double zre2 = zre * zre - zim * zim + re;
        double zim2 = 2.0 * zre * zim + im;
        zre = zre2;
        zim =zim2;

        if(zre * zre + zim * zim > 4.0){
            return i + 1;
        }
    }

    return max_inter;
}

int mandelbrot_intensity(int interacoes, int max_inter){
    return (int)((double)interacoes * 255.0/(double)max_inter);
}