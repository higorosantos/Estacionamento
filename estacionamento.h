#include "carro.h"
#include "fileira.h"
#include "rua.h"
#include "utils.h"

//typedef struct _estacionamento Estacionamento;

typedef struct _estacionamento {

    Pilha **fileiras;
    Rua *rua;
    int qtdFileiras;
    int totalVagas;

}Estacionamento;

Estacionamento* criar_estacionamento(int qtdFileiras, int maxFileira, int maxRua);

void liberar(Estacionamento *estaci);

int inserir_carro(Estacionamento *estaci, Carro *carro, int fileira);



//RETORNA A FILEIRA RECOMENDADA PARA O ARMAZENAMENTO,SE POR ACASO TODAS
//AS FILEIRAS ESTIVEREM CHEIAS RETORNA -1
int procurar_vaga(Estacionamento *estaci, Carro *carro);

int remover_carro(Estacionamento *estaci, char *placa);

void imprime_estaci(Estacionamento *estaci);

void imprime_rua(Estacionamento *estaci);
