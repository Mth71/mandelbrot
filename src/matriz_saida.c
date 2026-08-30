#include <stdio.h>
#include "matriz_saida.h"

int escrever_matriz(const char*filename, int *intensidades, int largura, int altura){
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