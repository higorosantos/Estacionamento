#include "estacionamento.h"

Estacionamento* criar_estacionamento(int qtdFileiras, int maxFileiras, int maxRua){

    Estacionamento *estaci = (Estacionamento*)malloc(sizeof(Estacionamento));

    if(estaci == NULL){

        return NULL;

    }

    estaci->fileiras = (Pilha**)malloc(qtdFileiras * sizeof(Pilha*));

    if(estaci == NULL){

        free(estaci);
        return NULL;

    }

    estaci->rua = criar_rua(maxRua);

    if(estaci->rua == NULL){

        free(estaci->rua);
        free(estaci);
        return NULL;
    }

    for(int i = 0; i < qtdFileiras; i++){

        estaci->fileiras[i] = pilha_cria(maxFileiras);


        if(estaci->fileiras[i] == NULL){

            free(estaci->fileiras);
            free(estaci->rua);
            free(estaci);

            return NULL;
        }

    }

    estaci->qtdFileiras = qtdFileiras;

    //Define um maximo de vagas disponiveis no estacionamento
    if(maxRua + 1 >= maxFileiras){
        estaci->totalVagas = qtdFileiras * maxFileiras;
    } else {
        estaci->totalVagas = qtdFileiras * maxFileiras - (maxFileiras - maxRua) + 1;
    }

    return estaci;
}

//RETORNA 1 SE FOR INSERIDO COM SUCESSO OU RETORNA -1 SE A FILEIRA ESCOLHIDA
//ESTIVER CHEIA.
int inserir_carro(Estacionamento *estaci, Carro *carro, int fileira){

    if(fileira < 0 || fileira > (estaci->qtdFileiras - 1)){

        return -1;

    }

    if(pilha_cheia(estaci->fileiras[fileira]) == 0){

        //printf("\n%d", fileira);

        pilha_push(estaci->fileiras[fileira] ,carro);
        estaci->totalVagas--;

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

int remover_carro(Estacionamento *estaci, char *placa){

    int fileira = -1;
    Carro *carro;

    for(int i = 0; i < estaci->qtdFileiras; i++){

        if(busca_carro(estaci->fileiras[i],placa) == 1){

            fileira = i;
            break;
        }

    }

    if(fileira == -1){
        return -1;
    }


    carro = pilha_pop(estaci->fileiras[fileira]);



    while(strcmp(placa, getPlaca(carro)) != 0){

        //resultado = inserir_rua(estaci->rua, carro);

        carro = pilha_pop(estaci->fileiras[fileira]);

    }

    //imprime_rua(estaci);

    free(carro);

    carro = remove_rua(estaci->rua);

    //printf("PLACA DO CARRO QUE ESTA SENDO POPADO: %s \n",getPlaca(carro));

    while(carro != NULL){

        //int teste = pilha_push(estaci->fileiras[fileira],carro);
        carro = remove_rua(estaci->rua);


    }

    return 1;

}

void imprime_estaci(Estacionamento *estaci){
    for(int i = 0; i < estaci->qtdFileiras; i++){
        mudar_cor(3);
        printf("|    |");
        mudar_cor(1);
        printf("\t--- Fileira %d ---\n", i + 1);
        mudar_cor(3);
        printf("| R ");
        imprime_carro(estaci->fileiras[i]);
        printf("| U ");
        imprime_placa(estaci->fileiras[i]);
        printf("| A ");
        imprime_tempo(estaci->fileiras[i]);
        printf("|    |\n");
    }
}

void imprime_rua(Estacionamento *estaci){
    mudar_cor(1);
    printf("\n\t--- RUA ---\n");
    mudar_cor(3);
    imprime_espaco(estaci->rua);
    imprime_placa_rua(estaci->rua);
    imprime_tempo_rua(estaci->rua);
    printf("\n\n");
}
