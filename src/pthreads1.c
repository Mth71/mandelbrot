#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthreads1.h"
#include "mandelbrot.h"
#include "common.h"

typedef struct{
    int *intensidades;
    int largura;
    int altura;
    int max_inter;
    int lin_inicio; //primeira linha que a thread calcula
    int lin_fim; //ultima linha que a thread calcuala
}threadsArgs1;

static void*worker(void *arg){
    threadsArgs1 *a = (threadsArgs1 *)arg;

    for(int lin = a->lin_inicio; lin < a->lin_fim; lin++){
        for(int col = 0; col < a->largura; col++){
            double re = X_MIN + col * (X_MAX - X_MIN) / a->largura;
            double im = Y_MIN + lin * (Y_MAX - Y_MIN)/ a->altura;

            int interacoes = mandelbrot_point(re, im, a->max_inter);
            int intensidade = mandelbrot_intensity(interacoes, a->max_inter);

            int idx = lin * a->largura + col;
            a->intensidades[idx] = intensidade;
        }
    }
    return NULL;
}

void mandelbrot_pthreads1(int *intensidades, int largura, int altura, int max_inter, int num_threads){
    pthread_t threads[num_threads];
    threadsArgs1 args[num_threads];

    int linhas_por_threads =altura / num_threads;
    int resto = altura % num_threads;

    int proxima_lin = 0;

    for(int i =0;i<num_threads;i++){
        int quantidade;
        if(i<resto){
            quantidade = linhas_por_threads + 1;
        }else{
            quantidade = linhas_por_threads;
        }

        args[i].intensidades = intensidades;
        args[i].largura = largura;
        args[i].altura = altura;
        args[i].max_inter = max_inter;
        args[i].lin_inicio = proxima_lin;
        args[i].lin_fim = proxima_lin + quantidade;

        proxima_lin += quantidade;

        pthread_create(&threads[i],NULL, worker, &args[i]);

    }
    for(int i =0; i<num_threads;i++){
        pthread_join(threads[i], NULL);
    }
}