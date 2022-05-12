#include "rua.h"

struct _rua {

    int n;
    int tam;
    Carro **arr;
};


Rua* criar_rua(int tam){

    Rua *rua = (Rua*)calloc(1,sizeof(Rua));


    if(rua == NULL){

        return NULL;

    }

    rua->arr = (Carro**)calloc(tam, sizeof(Carro*));

    if(rua->arr == NULL){

        free(rua);
        return NULL;

    }


    rua->tam = tam;
    rua->n = 0;

    return rua;

}


int inserir_rua(Rua* rua, Carro *carro)
{

     printf("PLACA DO CARRO NA RUA: %s", getPlaca(carro));

    if (rua->n == rua->tam) {

        return -1;
    }

    rua->arr[rua->n] = carro;



    rua->n++;

    return 1;
}

int rua_vazia(Rua *rua){

    if(rua->n == 0){

        return 1;
    }

    return -1;
}

int rua_cheia(Rua *rua){

    if(rua->n == rua->tam){

        return 1;
    }

    return -1;
}


int getTamRua(Rua *rua){

    return rua->tam;

}
//REMOVE DO INICIO
Carro* remove_rua(Rua *rua){

    Carro *aux = NULL;

    if (rua->n == 0) {

        return NULL;

    }

    aux = rua->arr[0];

    printf("PLACA DO CARRO SENDO REMOVIDO %s\n", getPlaca(aux));


    rua->arr[0] = NULL;



    rua->n--;

    for(int i = 0; i < rua->n; i++){

        rua->arr[i] = rua->arr[i + 1];

    }

    return aux;
}

void imprime_espaco(Rua *rua){
    for(int i = rua->tam-1; i >= 0; i--){
        printf(" |                ");
    }
    printf(" |\n");
}

void imprime_placa_rua(Rua *rua){
    for(int i = rua->tam-1; i >= 0; i--){
        printf(" | ");
            if(getPlaca(rua->arr[i]) == NULL){
                printf("   VAGA VAZIA  ");
            } else {
                printf(" placa: %s ",getPlaca(rua->arr[i]));
            }
    }
    printf(" |\n");
}

void imprime_tempo_rua(Rua *rua){
    for(int i = rua->tam-1; i >= 0; i--){
        printf(" | ");
            if(getPlaca(rua->arr[i]) == NULL){
                printf("               ");
            } else {
                printf("   tempo: %.2dhs  ",getPrevisaoRetirada(rua->arr[i]));
            }
    }
    printf(" |\n");
}
