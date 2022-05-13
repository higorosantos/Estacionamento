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
    estaci->tamFileiras = maxFileiras;

    //Define um maximo de vagas disponiveis no estacionamento
    if(maxRua + 1 >= maxFileiras){
        estaci->totalVagas = qtdFileiras * maxFileiras;
    } else {
        estaci->totalVagas = qtdFileiras * maxFileiras - (maxFileiras - maxRua) + 1;
    }

    Carro *carro1 = criar_carro("QWE1234", 2);
    Carro *carro2 = criar_carro("ASD1234", 2);
    Carro *carro3 = criar_carro("ZXC1234", 2);
    inserir_carro(estaci, carro1, 0);
    inserir_carro(estaci, carro2, 0);
    inserir_carro(estaci, carro3, 0);

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
    int aux = 99999;
    int aux2 = -99999;

    //VERIFICA SE TEM ALGUMA FILEIRA VAZIA/ FIZ UM FOR SEPARADO
    //PARA CASO OS PRIMEIROS NÃO FOREM VAZIO, NAO PASSAR POR TODOS AQUELES IF ALI DE BAIXO.
    for(int i = 0; i < estaci->qtdFileiras; i++){

         if(pilha_vazia(estaci->fileiras[i])){

            return i;

        }

    }


    //PERCORRE PELAS FILEIRAS VERIFICANDO O TOPO DELAS COMPARANDO COM A
    //PREVISÃO DE RETIRADA DO VEICULO QUE ESTA NO TOPO COM O QUE ESTA SENDO INSERIDO
    //VAI SEMPRE TENTAR ACHAR UMA FILEIRA QUE TEM UM CARRO COM O MAIOR PREVISÃO DE
    //RETIRADA E A MENOR DIFERENÇA DE TEMPO ENTRE
    //O CARRO QUE ESTA SENDO ADCIONADO E OQUE ESTA NO TOPO, SE POR ACASO NÃO HAVER UMA FILEIRA QUE CUMPRE ESSE CRITERIO
    //VAI PROCURAR A FILEIRA COM A MENOR DIFERENÇA DE TEMPO E QUE NÃO ESTEJA CHEIA
    for(int i = 0; i < estaci->qtdFileiras; i++){

     if(pilha_cheia(estaci->fileiras[i]) == 0 ){

        if(pilha_saida_topo(estaci->fileiras[i]) > getPrevisaoRetirada(carro)){

            if((pilha_saida_topo(estaci->fileiras[i]) - getPrevisaoRetirada(carro)) < aux){

                fileira = i;

                aux =  pilha_saida_topo(estaci->fileiras[i]) - getPrevisaoRetirada(carro);

            }

        }else{

             if(((pilha_saida_topo(estaci->fileiras[i]) - getPrevisaoRetirada(carro)) > aux2) && fileira == -1){

                fileira = i;
                aux2 = pilha_saida_topo(estaci->fileiras[i]) - getPrevisaoRetirada(carro);

            }
        }
      }
    }

    return fileira;

}


//PROCURAR VAGA PARA ARMAZENAR TEMPORARIAMENTE
//OS CARROS QUE VÃO SER MANOBRABOS QUANDO NÃO TIVER
//VAGA NA RUA / ELE RECEBE COMO PARAMETRO O FILEIRA
//ORIGINAL DELES PARA NÃO SEREM INSERIDOS TEMPORARIAMENTE LA.
//VAI RETORNA A PRIMEIRA FILEIRA COM VAGA.
int vaga_temporaria(Estacionamento *estaci, int fileira){

    for(int i = 0; i < estaci->qtdFileiras; i++){

        if(pilha_cheia(estaci->fileiras[i]) == 0 && i != fileira){

            return i;

        }

    }

    return -1;

}

//retorna o indice da fileira aonde esta o carro
int buscar_fileira_carro(Estacionamento *estaci, char *placa){
    int fileira;

    for(int i = 0; i < estaci->qtdFileiras; i++){
        if(busca_carro(estaci->fileiras[i],placa) == 1){
           fileira = i;
        }
    }
    return fileira;

}


int remover_carro(Estacionamento *estaci, char *placa){
    int *arrRemovidos;
    int fileira = buscar_fileira_carro(estaci, placa);

    if(fileira != -1){
        if(getTamRua(estaci->rua) < estaci->tamFileiras - 1){
            arrRemovidos = (int*)malloc((estaci->tamFileiras - getTamRua(estaci->rua)) * sizeof(int));
            printf("%d", (estaci->tamFileiras - getTamRua(estaci->rua)));
        }
        bagunca(estaci, placa, fileira, arrRemovidos);
        arruma(estaci, fileira, arrRemovidos);
    }
    return fileira;
}

int remover_carro_pausa(Estacionamento *estaci, char *placa){
    int *arrRemovidos;
    int fileira = buscar_fileira_carro(estaci, placa);

    if(fileira != -1){
        if(getTamRua(estaci->rua) < estaci->tamFileiras - 1){
            arrRemovidos = (int*)malloc((estaci->tamFileiras - getTamRua(estaci->rua)) * sizeof(int));
            printf("%d", (estaci->tamFileiras - getTamRua(estaci->rua)));
        }
        bagunca_pausa(estaci, placa, fileira, arrRemovidos);
        arruma_pausa(estaci, fileira, arrRemovidos);
    }
    return fileira;
}



void bagunca(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos){
    int tempVaga;
    int cont = 0;
    Carro *carro = pilha_pop(estaci->fileiras[fileira]);

    while(strcmp(placa, getPlaca(carro)) != 0){
        if(rua_cheia(estaci->rua) == -1){
            inserir_rua(estaci->rua, carro);
        }else{

            tempVaga = vaga_temporaria(estaci, fileira);
            inserir_carro(estaci, carro, tempVaga);
            arrRemovidos[cont] = tempVaga;
            cont++;
        }
        carro = pilha_pop(estaci->fileiras[fileira]);
    }
    //LIBERA A MEMORIA DO CARRO QUE VAI SER RETIRADO
    free(carro);
}

void bagunca_pausa(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos){
    int tempVaga;
    int cont = 0;
    Carro *carro = pilha_pop(estaci->fileiras[fileira]);

    while(strcmp(placa, getPlaca(carro)) != 0){
        if(rua_cheia(estaci->rua) == -1){
            inserir_rua(estaci->rua, carro);
            imprime_total(estaci);
            aperte_enter();
        }else{
            tempVaga = vaga_temporaria(estaci, fileira);
            inserir_carro(estaci, carro, tempVaga);
            imprime_total(estaci);
            arrRemovidos[cont] = tempVaga;
            cont++;
            aperte_enter();
        }
        carro = pilha_pop(estaci->fileiras[fileira]);
    }
    imprime_total(estaci);
    aperte_enter();
    //LIBERA A MEMORIA DO CARRO QUE VAI SER RETIRADO
    free(carro);
}

void arruma (Estacionamento *estaci, int fileira, int *arrRemovidos){
    Carro *carro;

    for(int i = 0; i < sizeof(arrRemovidos)/4; i++){
        int v = arrRemovidos[i];
        carro = pilha_pop(estaci->fileiras[v]);
        pilha_push(estaci->fileiras[fileira], carro);
    }
    //PASSAR OS CARRO DA RUA DE VOLTA PARA FILEIRA
    carro = remove_rua(estaci->rua);
    while(carro != NULL){
        pilha_push(estaci->fileiras[fileira], carro);
        carro = remove_rua(estaci->rua);
    }
    free(carro);
    free(arrRemovidos);
}

void arruma_pausa (Estacionamento *estaci, int fileira, int *arrRemovidos){
    Carro *carro;

    for(int i = 0; i < sizeof(arrRemovidos)/4; i++){
        int v = arrRemovidos[i];
        carro = pilha_pop(estaci->fileiras[v]);
        pilha_push(estaci->fileiras[fileira], carro);
        imprime_total(estaci);
        aperte_enter();
    }
    //PASSAR OS CARRO DA RUA DE VOLTA PARA FILEIRA
    carro = remove_rua(estaci->rua);
    while(carro != NULL){
        pilha_push(estaci->fileiras[fileira], carro);
        carro = remove_rua(estaci->rua);
        imprime_total(estaci);
        aperte_enter();
    }
    free(carro);
    free(arrRemovidos);
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

void adiciona_goiaba(Estacionamento *estaci, int fileira){
    Carro *carro = criar_carro("-1", -1);
    inserir_carro(estaci, carro, fileira);
}

void imprime_goiaba(Estacionamento *estaci, int fileira){
    Carro *aux = NULL;
    adiciona_goiaba(estaci, fileira);
    imprime_estaci(estaci);
    aux = pilha_pop(estaci->fileiras[fileira]);
    free(aux);
    estaci->totalVagas++;
}

