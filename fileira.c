#include "fileira.h"

struct _pilha {

    Carro **arr;
    //NUMERO DE ELEMENTO NA PILHA
    int n;
    //TAMANHO MAXIMO DE ELEMENTOS NA PILHA
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

int pilha_push(Pilha *pilha, Carro *carro){

    if(pilha->n == pilha->tam){

        return 0;

    }

    if(carro == NULL){

        return -1;
    }


    pilha->arr[pilha->n] = carro;

    pilha->n++;

    return 1;

}



Carro* pilha_pop(Pilha *pilha){

    if(pilha->n == 0){

        return NULL;

    }

    //free(pilha->arr[pilha->n - 1]);
    pilha->n--;

    return pilha->arr[pilha->n];

}

int pilha_vazia(Pilha *pilha){

    if(pilha->n == 0){

        return 1;

    }

    return 0;
}

int pilha_cheia(Pilha *pilha){

    if(pilha->n == pilha->tam){

        return 1;

    }

    return 0;
}


//RETORNA A PREVISÃO DE SAIDA DO CARRO DO TOPO DA PILHA
int pilha_saida_topo(Pilha *p){

    return getPrevisaoRetirada(p->arr[p->n - 1]);

}

//PROCURA O CARRO PELA PLACA VERIFICANDO SE ELA ESTA NESSA FILEIRA RETORNADO 1 SE SIM E -1 SE NÃO
int busca_carro(Pilha *p, char placa[TAM_PLACA]){


    for(int i = 0; i < p->n; i++){

        if(strcmp(placa, getPlaca(p->arr[i])) == 0){

            return 1;

        }

    }

    return -1;
}


