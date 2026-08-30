#ifndef MANDELBROT_H
#define MANDELBROT_H

//calcula quantas interações a formúla z = z²+c executa ate escapar de (|2| > 2) para o ponto (re, im).
//retorna um valor entre 1 e o máximo de interações
//se escapa na k-esima aplicação da formula , retorna k
//se nunca escapou retorna max de interações

int mandelbrot_point(double re, double im, int max_inter);


//converte a contagem de interações em uma intensidade de pixels 0-255;

int mandelbrot_intensity(int interacoes, int max_inter);

#endif