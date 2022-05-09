#include "carro.h"
#include "fileira.h"

//typedef struct _estacionamento Estacionamento;

typedef struct _estacionamento {

    Pilha **fileiras;
    int qtdFileiras;
    int tamFileiras;

}Estacionamento;

Estacionamento* criar_estacionamento(int qtdFileiras, int maxFileira);

void liberar(Estacionamento *estaci);

int inserir_carro(Estacionamento *estaci, Carro *carro, int fileira);



//RETORNA A FILEIRA RECOMENDADA PARA O ARMAZENAMENTO,SE POR ACASO TODAS
//AS FILEIRAS ESTIVEREM CHEIAS RETORNA -1
int procurar_vaga(Estacionamento *estaci, Carro *carro);


