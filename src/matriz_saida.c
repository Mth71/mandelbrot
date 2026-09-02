#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "matriz_saida.h"


int escrever_matriz(const char* filename, int *intensidades, int largura, int altura){

    FILE *f = fopen(filename, "w");

    if(f == NULL){
        return -1;
    }

    for(int lin = 0; lin < altura; lin++){

        for(int col = 0; col < largura; col++){

            int idx = lin * largura + col;

            if(col > 0){
                fprintf(f, " ");
            }

            fprintf(f, "%d", intensidades[idx]);
        }

        fprintf(f, "\n");
    }

    fclose(f);

    return 0;
}


//Argumentos das threads da pthreads2
typedef struct {

    int *intensidades;
    int largura;
    int altura;

    int thread_id;
    int num_threads;

    char *saida;

    size_t tamanho_linha;

} threadsArgs2;


//Cada thread prepara algumas linhas da saída 
static void *worker_saida(void *arg){

    threadsArgs2 *a = (threadsArgs2 *)arg;

    for(int lin = a->thread_id;
        lin < a->altura;
        lin += a->num_threads){

        char *linha = a->saida + ((size_t)lin * a->tamanho_linha);

        int pos = 0;

        for(int col = 0; col < a->largura; col++){

            int idx = lin * a->largura + col;

            if(col > 0){
                pos += snprintf(linha + pos,a->tamanho_linha - pos," ");
            }

            pos += snprintf(linha + pos,a->tamanho_linha - pos,"%d",a->intensidades[idx]);
        }

        snprintf(linha + pos,a->tamanho_linha - pos,"\n");
    }

    return NULL;
}


int escrever_matriz_pthreads2(const char* filename,int *intensidades,int largura,int altura,int num_threads){
    FILE *f = fopen(filename, "w");

    if(f == NULL){
        return -1;
    }

    size_t tamanho_linha = (size_t)largura * 12 + 2; // cada pixel pode ocupar no maximo 11 caracteres para int e 1 para espaco coloco largura *12+2 pra ter margem

    char *saida = malloc((size_t)altura * tamanho_linha);

    if(saida == NULL){
        fclose(f);
        return -1;
    }

    pthread_t threads[num_threads];

    threadsArgs2 args[num_threads];


    //Criação das threads
    for(int i = 0; i < num_threads; i++){

        args[i].intensidades = intensidades;
        args[i].largura = largura;
        args[i].altura = altura;
        args[i].thread_id = i;
        args[i].num_threads = num_threads;
        args[i].saida = saida;
        args[i].tamanho_linha = tamanho_linha;

        int erro=pthread_create(&threads[i],NULL,worker_saida,&args[i]);
        if(erro != 0 ){
            fprintf(stderr, "erro: falha ao criar thread %d (código %d)\n", i, erro);
            for(int j =0; j<i;j++){
                pthread_join(threads[j], NULL);
            }
            free(saida);
            fclose(f);
            return -1;
        }

    }


    //Espera todas as threads terminarem 
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }


  //Agr a thread principal escreve as linhas na ordem certa 
    for(int lin = 0; lin < altura; lin++){

        char *linha = saida + ((size_t)lin * tamanho_linha);

        fputs(linha, f);
    }


    free(saida);

    fclose(f);

    return 0;
}