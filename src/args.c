#include <stdio.h>
#include <stdlib.h>
#include "args.h"

int parse_args(int argc, char*argv[], config*cfg){
    if(argc != 5){
        fprintf(stderr, "uso: %s <largura> <altura> <max_interacoes> <num_threads>\n", argv[0]);
        return -1;
    }

    char *end;

    long largura = strtol(argv[1], &end, 10);
    if(*end != '\0' || largura <= 0){
        fprintf(stderr, "erro: largura inválida (%s). (precisa ser um inteiro positivo)\n", argv[1]);
        return -1;
    }

    long altura = strtol(argv[2], &end, 10);
    if(*end != '\0' || altura <= 0){
        fprintf(stderr, "erro: altura inválida (%s). (precisa ser um inteiro positivo)\n", argv[2]);
        return -1;
    }


        long max_inter = strtol(argv[3], &end, 10);
    if(*end != '\0' || max_inter <= 0){
        fprintf(stderr, "erro: número máximo de interações inválido (%s). (precisa ser um inteiro positivo)\n", argv[3]);
        return -1;
    }


        long num_threads = strtol(argv[4], &end, 10);
    if(*end != '\0' || num_threads <= 0){
        fprintf(stderr, "erro: número de threads inválido (%s). (precisa ser um inteiro positivo)\n", argv[4]);
        return -1;
    }

    cfg->altura = (int)altura;
    cfg->largura = (int)largura;
    cfg->max_inter = (int)max_inter;
    cfg->num_threads = (int)num_threads;

    return 0;
}
