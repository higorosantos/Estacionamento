#include "carro.h"


typedef struct _pilha Pilha;


Pilha* pilha_cria(int tam);

int pilha_push(Pilha *pilha, Carro *carro);

Carro* pilha_pop(Pilha *pilha);

int pilha_vazia(Pilha *pilha);

int busca_carro(Pilha *p, char placa[TAM_PLACA]);

int pilha_cheia(Pilha *pilha);

//RETORNA A PREVISÃO DE SAIDA DO CARRO DO TOPO DA PILHA
int pilha_saida_topo(Pilha *p);
