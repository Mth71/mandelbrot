#include "serial.h"
#include "mandelbrot.h"
#include "common.h"

void mandelbrot_serial(int *intensidades, int largura, int altura, int max_inter) {
    for (int lin = 0; lin < altura; lin++) {
        for (int col = 0; col < largura; col++) {
            double re = X_MIN + col * (X_MAX - X_MIN) / largura;
            double im = Y_MIN + lin * (Y_MAX - Y_MIN) / altura;

            int interacoes = mandelbrot_point(re, im, max_inter);
            int intensidade = mandelbrot_intensity(interacoes, max_inter);

            int idx = lin * largura + col;
            intensidades[idx] = intensidade;
        }
    }
}