#include "carro.h"


typedef struct _pilha Pilha;


Pilha* pilha_cria(int tam);

int pilha_push(Pilha *pilha, char placa[7], int provisaoRetirada);

int pilha_pop(Pilha *pilha);

int pilha_vazia();
