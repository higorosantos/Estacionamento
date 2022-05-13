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

    estaci->rua = pilha_cria(maxRua);

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


    if(pilha_cheia(estaci->fileiras[fileira]) == -1){

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
    //PARA CASO OS PRIMEIROS N�O FOREM VAZIO, NAO PASSAR POR TODOS AQUELES IF ALI DE BAIXO.
    for(int i = 0; i < estaci->qtdFileiras; i++){

         if(pilha_vazia(estaci->fileiras[i])){

            return i;

        }

    }


    //PERCORRE PELAS FILEIRAS VERIFICANDO O TOPO DELAS COMPARANDO COM A
    //PREVIS�O DE RETIRADA DO VEICULO QUE ESTA NO TOPO COM O QUE ESTA SENDO INSERIDO
    //VAI SEMPRE TENTAR ACHAR UMA FILEIRA QUE TEM UM CARRO COM O MAIOR PREVIS�O DE
    //RETIRADA E A MENOR DIFEREN�A DE TEMPO ENTRE
    //O CARRO QUE ESTA SENDO ADCIONADO E OQUE ESTA NO TOPO, SE POR ACASO N�O HAVER UMA FILEIRA QUE CUMPRE ESSE CRITERIO
    //VAI PROCURAR A FILEIRA COM A MENOR DIFEREN�A DE TEMPO E QUE N�O ESTEJA CHEIA
    for(int i = 0; i < estaci->qtdFileiras; i++){
     if(pilha_cheia(estaci->fileiras[i]) == -1 ){
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
//OS CARROS QUE V�O SER MANOBRABOS QUANDO N�O TIVER
//VAGA NA RUA / ELE RECEBE COMO PARAMETRO O FILEIRA
//ORIGINAL DELES PARA N�O SEREM INSERIDOS TEMPORARIAMENTE LA.
//VAI RETORNA A PRIMEIRA FILEIRA COM VAGA.
int vaga_temporaria(Estacionamento *estaci, int fileira){
    for(int i = 0; i < estaci->qtdFileiras; i++){
        if(pilha_cheia(estaci->fileiras[i]) == -1 && i != fileira){
            return i;
        }
    }
    return -1;
}

//retorna o indice da fileira aonde esta o carro
int buscar_fileira_carro(Estacionamento *estaci, char *placa){
    int fileira = -1;

    for(int i = 0; i < estaci->qtdFileiras; i++){
        if(busca_carro(estaci->fileiras[i],placa) == 1){
           fileira = i;
        }
    }
    return fileira;
}

int getTotalVagas(Estacionamento *estaci){
    return estaci->totalVagas;
}

int remover_carro(Estacionamento *estaci, char *placa){

    int *arrRemovidos = NULL;
    int fileira = buscar_fileira_carro(estaci, placa);
    Carro *carro = NULL;

    if(fileira != -1){
        carro = pilha_pop(estaci->fileiras[fileira]);
        //COMPARA SE O TOPO DA FILA JA � O CARRO QUE QUEREMOS REMOVER
        //SE FOR JA LIBERA ELE ANTES DE PASSAR POR TODOS AS VERIFICA��ES
        if(strcmp(placa, getPlaca(carro)) == 0){
            free(carro);
            estaci->totalVagas++;
            return fileira;

        }
        //VERIFICA SE A RUA TEM VAGA SUFICIENTE PARA FAZER AS MANOBRAS
        //SE NAO TIVER ELE MALLOCA UM ARRAY DE INTEIROS PARA ARMAZENAR
        //EM QUAL FILEIRA OS CARRO FORAM COLOCADOS.
        if(pilha_tam_max(estaci->rua) < estaci->tamFileiras - 1){
            arrRemovidos = (int*)malloc((estaci->tamFileiras - pilha_tam_max(estaci->rua)) * sizeof(int));
        }
        bagunca(estaci, placa, fileira, arrRemovidos, carro);
        arruma(estaci, fileira, arrRemovidos);
        estaci->totalVagas++;
    }
    return fileira;
}

int remover_carro_pausa(Estacionamento *estaci, char *placa){

    int *arrRemovidos = NULL;
    int fileira = buscar_fileira_carro(estaci, placa);
    Carro *carro = NULL;

    if(fileira != -1){
        carro = pilha_pop(estaci->fileiras[fileira]);
        //COMPARA SE O TOPO DA FILA JA � O CARRO QUE QUEREMOS REMOVER
        //SE FOR JA LIBERA ELE ANTES DE PASSAR POR TODOS AS VERIFICA��ES
        if(strcmp(placa, getPlaca(carro)) == 0){
            free(carro);
            estaci->totalVagas++;
            return fileira;
        }
        if(pilha_tam_max(estaci->rua) < estaci->tamFileiras - 1){
            arrRemovidos = (int*)malloc((estaci->tamFileiras - pilha_tam_max(estaci->rua)) * sizeof(int));
        }
        bagunca_pausa(estaci, placa, fileira, arrRemovidos, carro);
        arruma_pausa(estaci, fileira, arrRemovidos);
        estaci->totalVagas++;
    }
    return fileira;
}

void bagunca(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos, Carro* carro){
    int tempVaga;
    int cont = 0;

    while(strcmp(placa, getPlaca(carro)) != 0){
        if(pilha_cheia(estaci->rua) == -1){
            pilha_push(estaci->rua, carro);
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

void bagunca_pausa(Estacionamento *estaci, char *placa, int fileira, int *arrRemovidos, Carro *carro){
    int tempVaga;
    int cont = 0;

    while(strcmp(placa, getPlaca(carro)) != 0){
        if(pilha_cheia(estaci->rua) == -1){
            pilha_push(estaci->rua, carro);
            system("cls");
            printf("\n\n");
            imprime_estaci(estaci);
            imprime_rua(estaci);
            aperte_enter();
        }else{
            tempVaga = vaga_temporaria(estaci, fileira);
            inserir_carro(estaci, carro, tempVaga);
            system("cls");
            printf("\n\n");
            imprime_estaci(estaci);
            imprime_rua(estaci);
            arrRemovidos[cont] = tempVaga;
            cont++;
            aperte_enter();
        }
        carro = pilha_pop(estaci->fileiras[fileira]);
    }
    system("cls");
    printf("\n\n");
    imprime_estaci(estaci);
    imprime_rua(estaci);
    aperte_enter();
    //LIBERA A MEMORIA DO CARRO QUE VAI SER RETIRADO
    free(carro);
}

void arruma (Estacionamento *estaci, int fileira, int *arrRemovidos){
    Carro *carro;

    //PERCORRER PELO ARRAY DOS CARRO QUE FORAM
    //MOVIDOS PARA OUTRAS FILEIRAS PARA PODER MANOBRAR
    //E RETORNA ELE A FILEIRA ORIGINAL
    if((estaci->tamFileiras - pilha_tam_max(estaci->rua)) > 0){
        for(int i = 0; i < sizeof(arrRemovidos)/4; i++){
            int v = arrRemovidos[i];
            carro = pilha_pop(estaci->fileiras[v]);
            pilha_push(estaci->fileiras[fileira], carro);
        }
        free(arrRemovidos);
    }
    //PASSAR OS CARRO DA RUA DE VOLTA PARA FILEIRA
    carro = pilha_pop(estaci->rua);
    while(carro != NULL){
        pilha_push(estaci->fileiras[fileira], carro);
        carro = pilha_pop(estaci->rua);
    }

}

void arruma_pausa (Estacionamento *estaci, int fileira, int *arrRemovidos){
    Carro *carro;

    if((estaci->tamFileiras - pilha_tam_max(estaci->rua)) > 0){
        for(int i = 0; i < sizeof(arrRemovidos)/4; i++){
            int v = arrRemovidos[i];
            carro = pilha_pop(estaci->fileiras[v]);
            pilha_push(estaci->fileiras[fileira], carro);
            system("cls");
            printf("\n\n");
            imprime_estaci(estaci);
            imprime_rua(estaci);
            aperte_enter();
        }
        free(arrRemovidos);
    }
    //PASSAR OS CARRO DA RUA DE VOLTA PARA FILEIRA
    carro = pilha_pop(estaci->rua);
    while(carro != NULL){
        pilha_push(estaci->fileiras[fileira], carro);
        system("cls");
        printf("\n\n");
        imprime_estaci(estaci);
        imprime_rua(estaci);
        aperte_enter();
        carro = pilha_pop(estaci->rua);
    }

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

void imprime_total(Estacionamento * estaci){
    if(estaci == NULL){
        system("cls");
        imprime_erro("\tESTACIONAMENTO N�O CONFIGURADO!");
    }else{
        mudar_cor(1);
        printf("\n\t--- ESTACIONAMENTO - TOTAL DE VAGAS: %d ---\n\n", getTotalVagas(estaci));
        mudar_cor(3);
        imprime_estaci(estaci);
        imprime_rua(estaci);
    }
}

