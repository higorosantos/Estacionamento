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
    printf("\n%s\n", erro);
    cor_padrao();
}


void imprime_sucesso(char sucesso[MSG_SIZE]) {

    mudar_cor(10);
    printf("\n%s\n", sucesso);
    cor_padrao();
}

void aperte_enter(){

    mudar_cor(8);
    printf("\nPressione ENTER para continuar.");
    getchar();
    system("cls");
    cor_padrao();
}

void imprimir_colorido(char msg[MSG_SIZE], int cor){

    mudar_cor(cor);
    printf("%s", msg);
    cor_padrao();

}

void limparBuffer(){

    char a;

    while((a = getchar() != '\n'));

}

