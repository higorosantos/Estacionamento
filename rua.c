#include "rua.h"

struct _no{

    Carro *carro;
    struct _no *prox;

};

struct _rua {

    No *inicio;
    No *fim;
    int n;
    int tam;

};


Rua* cria_fila(int tam){

    Rua *fila = (Rua*)malloc(sizeof(Rua));

    fila->inicio = NULL;
    fila->fim = NULL;

    fila->n = 0;
    fila->tam = tam;

}

int insere_fila(Rua* rua, Carro *carro){

    if(rua->n == rua->tam){

        return -1;

    }


    No *novoNo = (No*)malloc(sizeof(No));


    if(novoNo == NULL){

        return -1;

    }

    novoNo->carro = carro;
    novoNo->prox = NULL;

    if(rua->inicio != NULL){

        rua->fim->prox = novoNo;

    }else{

        rua->inicio = novoNo;

    }

    rua->fim = novoNo;
    rua->n++;

    return 1;
}

int fila_vazia(Rua *rua){

    if(rua->inicio == NULL){

        return 1;
    }

    return 0;
}

int remove_fila(Rua *rua){

    if(fila_vazia(rua) == 0){

        return 0;
    }

    rua->inicio = rua->inicio->prox;
    rua->n--;

    return 1;
}

