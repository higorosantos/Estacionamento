#include "rua.h"

struct _rua {

    int n;
    int ini;
    int tam;

    Carro **arr;
};


Rua* cria_fila(int tam){

    Rua *fila = (Rua*)malloc(sizeof(Rua));


    if(fila == NULL){

        return NULL;

    }

    fila->arr = (Carro**)malloc(tam * sizeof(Carro*));

    if(fila->arr == NULL){

        free(fila);
        return NULL;

    }

    fila->ini = 0;
    fila->tam = tam;

    fila->n = 0;

    return fila;

}


int insere_fila(Rua* rua, Carro *carro)
{
    int fim;
    if (rua->n == rua ) {

        return -1;
    }

    fim = (rua->ini + rua->n) % rua->tam;
    rua->arr[fim] = carro;
    rua->n++;


    return 1;

}

int fila_vazia(Rua *rua){

    if(rua->n == 0){

        return 1;
    }

    return -1;
}

Carro* remove_fila(Rua *rua){

    Carro *aux = NULL;

    if (rua->n == 0) {

        return NULL;

    }

    aux = rua->arr[rua->ini];
    rua->ini = (rua->ini + 1) % rua->tam;
    rua->n--;

    return aux;
}

void imprime_placa_rua(Rua *rua){
    for(int i = rua->tam-1; i >= 0; i--){
        printf(" | ");
            if(getPlaca(rua->arr[i]) == NULL){
                printf("     PLACA     ");
            } else {
                printf(" placa: %s ",getPlaca(rua->arr[i]));
            }
    }
    printf(" |\n");
}

void imprime_tempo_rua(Rua *rua){
    for(int i = rua->tam-1; i >= 0; i--){
        printf(" | ");
            if(getPlaca(rua->arr[i]) == NULL){
                printf("     TEMPO     ");
            } else {
                printf("   tempo: %.2dhs  ",getPrevisaoRetirada(rua->arr[i]));
            }
    }
    printf(" |\n");
}
