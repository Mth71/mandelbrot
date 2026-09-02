#ifndef MATRIZ_H
#define MATRIZ_H

//escreve a matriz de intensidade no arquivo indicado

int escrever_matriz(const char*filename, int *intensidades, int largura, int altura);

int escrever_matriz_pthreads2(const char*filename, int *intensidades, int largura, int altura, int num_threads);

#endif

