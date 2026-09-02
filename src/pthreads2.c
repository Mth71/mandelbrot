#include "pthreads2.h"
#include "serial.h"
#include "matriz_saida.h"

void mandelbrot_pthreads2(int*intensidades, int largura, int altura, int max_inter, int num_threads){
    mandelbrot_serial(intensidades, largura, altura, max_inter); //calcula de forma serial
    escrever_matriz_pthreads2("mandelbrot_mcr_pthreads2.pmg", intensidades, largura,altura,num_threads);
}