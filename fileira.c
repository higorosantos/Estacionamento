#include "fileira.h"

struct _pilha {

    Carro **arr;
    //Numero de elementos
    int n;
    //tamanho maximo de elementos
    int tam;

};


//Recebe como parametro o tamanho max de carro da fileira
Pilha* pilha_cria(int tam){

    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));

    if(pilha == NULL){

        return NULL;
    }

    pilha->arr= (Carro**)malloc(tam * sizeof(Carro*));

    if(pilha->arr == NULL){

        free(pilha);
        return NULL;

    }

    pilha->n = 0;
    pilha->tam = tam;

    return pilha;

}

int pilha_push(Pilha *pilha, char placa[TAM_PLACA], int previsaoRetirada){

    if(pilha->n == pilha->tam){

        return 0;

    }


    Carro *novo = criar_carro(placa, previsaoRetirada);

    if(novo == NULL){

        return -1;
    }

    printf("\n%d", novo->placa);

    pilha->arr[pilha->n] = novo;

    pilha->n++;

    return 1;

}



int pilha_pop(Pilha *pilha){

    if(pilha->n == 0){

        return -1;

    }

    free(pilha->arr[pilha->n - 1]);
    pilha->n--;

    return 1;

}

int pilha_vazia(Pilha *pilha){

    if(pilha->n == 0){

        return 1;

    }

    return 0;
}


