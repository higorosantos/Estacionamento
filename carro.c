#include "carro.h"


struct _carro{

    char placa[TAM_PLACA];
    int previsaoRetirada;

};

Carro* criar_carro(char placa[TAM_PLACA], int previsaoRetirada){

    Carro *newCarro = (Carro*)malloc(sizeof(Carro));

    if(newCarro == NULL){

        return NULL;

    }

    newCarro->previsaoRetirada = previsaoRetirada;
    strcpy(newCarro->placa, placa);

    return newCarro;
}

char* getPlaca(Carro* carro){

    return carro->placa;

}


int getPrevisaoRetirada(Carro *carro){

    return carro->previsaoRetirada;

}
