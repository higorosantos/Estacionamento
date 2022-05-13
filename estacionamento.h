#include "carro.h"
#include "fileira.h"
#include "rua.h"
#include "utils.h"

#define TEMP_MAX_RETIRADA 72
//typedef struct _estacionamento Estacionamento;

typedef struct _estacionamento {

    Pilha **fileiras;
    Rua *rua;
    int qtdFileiras;
    int tamFileiras;
    int totalVagas;

}Estacionamento;

Estacionamento* criar_estacionamento(int qtdFileiras, int maxFileira, int maxRua);

void liberar(Estacionamento *estaci);

int inserir_carro(Estacionamento *estaci, Carro *carro, int fileira);

int getTotalVagas(Estacionamento *estaci);

//RETORNA A FILEIRA RECOMENDADA PARA O ARMAZENAMENTO,SE POR ACASO TODAS
//AS FILEIRAS ESTIVEREM CHEIAS RETORNA -1
int procurar_vaga(Estacionamento *estaci, Carro *carro);

int vaga_temporaria(Estacionamento *estaci, int fileira);

int remover_carro(Estacionamento *estaci, char *placa);

void imprime_estaci(Estacionamento *estaci);

void imprime_rua(Estacionamento *estaci);

int remover_carro_pausa(Estacionamento *estaci, char *placa);

void bagunca(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos, Carro *carro);

void bagunca_pausa(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos, Carro *carro);

void arruma (Estacionamento *estaci, int fileira, int *arrRemovidos);

void arruma_pausa (Estacionamento *estaci, int fileira, int *arrRemovidos);

int buscar_fileira_carro(Estacionamento *estaci, char *placa);

void imprime_total(Estacionamento *estaci);

void imprime_goiaba(Estacionamento *estaci, int fileira);
