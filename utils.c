#include "utils.h"

void mudar_cor(int cor){

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void cor_padrao(){

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);

}

void imprime_erro(char erro[MSG_SIZE]) {

    mudar_cor(4);
    printf("\n\t%s\n", erro);
    cor_padrao();
}


void imprime_sucesso(char sucesso[MSG_SIZE]) {

    mudar_cor(10);
    printf("\n\t%s\n", sucesso);
    cor_padrao();
}

void aperte_enter(){

    fflush(stdin);
    mudar_cor(8);
    printf("\n\tPressione ENTER para continuar.");
    getchar();
    system("cls");
    cor_padrao();
}

void imprimir_colorido(char msg[MSG_SIZE], int cor){

    mudar_cor(cor);
    printf("%s", msg);
    cor_padrao();

}

void string_maiuscula(char *str){

        int tam = (sizeof str / sizeof str[0]) - 1;


        for(int i = 0; i < tam; i++){

            str[i] = toupper(str[i]);

        }


}
