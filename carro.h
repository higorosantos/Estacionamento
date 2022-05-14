#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_PLACA 8

typedef struct _carro Carro;


Carro* criar_carro(char placa[TAM_PLACA], int previsaoRetirada);

char* getPlaca(Carro* carro);

int getPrevisaoRetirada(Carro *carro);
