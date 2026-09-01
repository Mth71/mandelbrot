#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "serial.h"
#include "matriz_saida.h"
#include "timer.h"
#include "openmp.h"

int main(int argc, char *argv[]) {
    config cfg;

    if (parse_args(argc, argv, &cfg) != 0) {
        return 1;
    }

    int *intensidades = malloc(sizeof(int) * cfg.largura * cfg.altura);
    if (intensidades == NULL) {
        fprintf(stderr, "erro: falha ao alocar memoria para a imagem\n");
        return 1;
    }

    FILE *times = fopen("times.txt", "w");
    if (times == NULL) {
        fprintf(stderr, "erro: falha ao criar times.txt\n");
        free(intensidades);
        return 1;
    }

    Timer t;

   // serial
    timer_start(&t);
    mandelbrot_serial(intensidades, cfg.largura, cfg.altura, cfg.max_inter);
    timer_stop(&t);

    char filename[256];
    snprintf(filename, sizeof(filename), "mandelbrot_mcr_serial.pgm");
    if (escrever_matriz(filename, intensidades, cfg.largura, cfg.altura) != 0) {
        fprintf(stderr, "erro: falha ao criar arquivo de saida '%s'\n", filename);
        fclose(times);
        free(intensidades);
        return 1;
    }
    
    
    fprintf(times, "serial: %.6f segundos\n", timer_elapsed_seconds(&t));
  
    
    //openMP
    timer_start(&t);
    mandelbrot_openmp(intensidades, cfg.largura, cfg.altura, cfg.max_inter, cfg.num_threads);
    timer_stop(&t);

    snprintf(filename, sizeof(filename), "mandelbrot_mcr_openmp.pmg");
    if(escrever_matriz(filename, intensidades, cfg.largura, cfg.altura) != 0){
        fprintf(stderr, "erro: falha ao criar arquivo de saida '%s'\n", filename);
        fclose(times);
        free(intensidades);
        return 1;
    }
    fprintf(times, "openmp: %.6f segundos\n", timer_elapsed_seconds(&t));

    fclose(times);
    free(intensidades);
    return 0;



}