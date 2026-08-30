#ifndef ARGS_H
#define ARGS_H

typedef struct{
    int largura;
    int altura;
    int max_inter;
    int num_threads;
}config;

//faz o parsing e a validação do argv. retorna 0 caso de certo, ou -1 se algum argumento for invalido (mensagem de errro impressa no stderr)

int parse_args(int argc, char*argv[], config*cfg);

#endif