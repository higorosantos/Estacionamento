#include "estacionamento.h"

Estacionamento* criar_estacionamento(int qtdFileiras, int maxFileiras){

    Estacionamento *estaci = (Estacionamento*)malloc(sizeof(Estacionamento));

    if(estaci == NULL){

        return NULL;

    }

    estaci->fileiras = (Pilha**)malloc(qtdFileiras * sizeof(Pilha*));


    if(estaci == NULL){

        free(estaci);
        return NULL;

    }

    for(int i = 0; i < qtdFileiras; i++){

        estaci->fileiras[i] = pilha_cria(maxFileiras);

        if(estaci->fileiras[i] == NULL){

            free(estaci->fileiras);
            free(estaci);

            return NULL;

        }

    }

    estaci->qtdFileiras = qtdFileiras;
    estaci->tamFileiras = maxFileiras;

    return estaci;
}


//RETORNA 1 SE FOR INSERIDO COM SUCESSO OU RETORNA -1 SE A FILEIRA ESCOLHIDA
//ESTIVER CHEIA.
int inserir_carro(Estacionamento *estaci, Carro *carro, int fileira){

    if(fileira < 0 || fileira > (estaci->qtdFileiras - 1)){

        return -1;

    }

    if(pilha_cheia(estaci->fileiras[fileira]) == 0){

        printf("\n%d", fileira);

        pilha_push(estaci->fileiras[fileira] ,carro);

        return 1;

    }

    return -1;

}

//RETORNA A FILEIRA RECOMENDADA PARA O ARMAZENAMENTO,SE POR ACASO TODAS
//AS FILEIRAS ESTIVEREM CHEIAS RETORNA -1
int procurar_vaga(Estacionamento *estaci, Carro *carro){

    int fileira = -1;
    int aux;


    for(int i = 0; i < estaci->qtdFileiras; i++){

        if(pilha_vazia(estaci->fileiras[i])){

            return i;

        }

    }

    //PERCORRE PELAS FILEIRAS VERIFICANDO O TOPO DELAS COMPARANDO COM A
    //PREVISÃO DE RETIRADA DO VEICULO QUE ESTA NO TOPO COM O QUE ESTA SENDO INSERIDO
    //VAI SEMPRE TENTAR ACHAR UMA FILEIRA QUE TEM UM CARRO COM O MAIOR PREVISÃO DE
    //RETIRADA NO TOPO E QUE NÃO ESTEJA CHEIA, SE POR ACASO NÃO HAVER UMA FILEIRA QUE CUMPRE ESSE CRITERIO
    //VAI PROCURAR A FILEIRA COM A MENOR DIFERENÇA DE TEMPO E QUE NÃO ESTEJA CHEIA
    for(int i = 0; i < estaci->qtdFileiras; i++){

        //printf("\n%d", pilha_saida_topo(estaci->fileiras[i]));

        printf("\n%d", getPrevisaoRetirada(carro));

        aux = getPrevisaoRetirada(carro) - pilha_saida_topo(estaci->fileiras[i]);



        if(pilha_saida_topo(estaci->fileiras[i]) > getPrevisaoRetirada(carro) && pilha_cheia(estaci->fileiras[i]) == 0){

            return i;

        }else if(pilha_cheia(estaci->fileiras[i]) == 0){


            if((getPrevisaoRetirada(carro) - pilha_saida_topo(estaci->fileiras[i])) <= aux){

                fileira = i;

            }

        }

    }

    return fileira;

}
