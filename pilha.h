#include "carro.h"
#include "utils.h"


typedef struct _pilha Pilha;


Pilha* pilha_cria(int tam);

int pilha_push(Pilha *pilha, Carro *carro);

Carro* pilha_pop(Pilha *pilha);

int pilha_vazia(Pilha *pilha);

int pilha_cheia(Pilha *pilha);

int pilha_tam_max(Pilha *pilha);
//RETORNA A PREVISÃO DE SAIDA DO CARRO DO TOPO DA PILHA
int pilha_saida_topo(Pilha *p);

//RETORNA A QUANTIDADE DE CARROS NA FILEIRA
int getQtdCarros(Pilha *pilha);

void imprime_espaco(Pilha *p);

void imprime_carro(Pilha *p);

void imprime_placa(Pilha *p);

void imprime_tempo(Pilha *p);

int pilha_tam_max(Pilha *pilha);

int busca_carro(Pilha *p, char placa[TAM_PLACA]);
