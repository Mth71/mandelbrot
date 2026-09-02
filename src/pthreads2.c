#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthreads2.h"
#include "mandelbrot.h"
#include "common.h"

typedef struct{
    int *intensidades;
    int largura;
    int altura;
    int max_inter;
    int thread_id;    //qaul thread eu sou?
    int num_threads;  //quantas trheads existem no total
}threadsArgs2;

static void *worker(void *arg){
    threadsArgs2*a=(threadsArgs2*)arg;

    for(int lin = a->thread_id; lin < a->altura; lin += a->num_threads){
        for(int col = 0; col < a->largura; col++){
            double re = X_MIN + col * (X_MAX - X_MIN) / a->largura;
            double im = Y_MIN + lin * (Y_MAX - Y_MIN) / a->altura;

            int interacoes = mandelbrot_point(re, im, a->max_inter);
            int intensidade = mandelbrot_intensity(interacoes, a->max_inter);

            int idx = lin * a->largura + col;
            a->intensidades[idx] = intensidade;
        }
    }

    return NULL;
}

void mandelbrot_pthreads2(int *intensidades, int largura, int altura, int max_inter, int num_threads){
    pthread_t threads[num_threads];
    threadsArgs2 args[num_threads];

    for(int i= 0; i<num_threads;i++ ){
        args[i].intensidades = intensidades;
        args[i].largura = largura;
        args[i].altura = altura;
        args[i].max_inter = max_inter;
        args[i].thread_id = i;
        args[i].num_threads = num_threads;

        pthread_create(&threads[i], NULL, worker, &args[i]);
    }
    for(int i = 0; i<num_threads;i++){
        pthread_join(threads[i], NULL);
    }
}