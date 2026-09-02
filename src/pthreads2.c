#include "pthreads2.h"
#include "serial.h"
#include "matriz_saida.h"

int mandelbrot_pthreads2(const char*filename,int*intensidades, int largura, int altura, int max_inter, int num_threads){
    mandelbrot_serial(intensidades, largura, altura, max_inter); //calcula de forma serial
    escrever_matriz_pthreads2("mandelbrot_mcr_pthreads2.pgm", intensidades, largura,altura,num_threads);
    return escrever_matriz_pthreads2(filename,intensidades,largura,altura,num_threads);
}