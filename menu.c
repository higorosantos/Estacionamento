#include "menu.h"


int interfaceMenuPrincipal(){


    int opcao;
    mudar_cor(1);
    printf("\n\n               ESTACIONAMENTO");
    printf("\n-------------------------------------------------");
    mudar_cor(11);
    printf("\n\n\t1. Configurar estacionamento.");
    printf("\n\t2. Mostrar estacionamento.");
    printf("\n\t3. Inserir carro.");
    printf("\n\t4. Remover carro.");
    printf("\n\t5. Remover passo a passo.");
    printf("\n\t0. Sair.");
    mudar_cor(3);
    printf("\n\nEntre com a opção desejada: ");
    scanf("%d", &opcao);
    return opcao;

}


//PARTE LOGICA DOS MENUS
void menuPrincipal() {

    Estacionamento *estaci = NULL;

    int opcao_menu = -1;
    while (opcao_menu != 0) {
        opcao_menu = interfaceMenuPrincipal();
        switch(opcao_menu) {
            case 1:
                estaci = interfaceConfigurarEstacionamento(estaci);
                break;
            case 2:
                if(estaci == NULL){
                    system("cls");
                    imprime_erro("ESTACIONAMENTO NÃO CONFIGURADO!");
                }else{
                    imprime_estaci(estaci);
                    imprime_rua(estaci);
                }
                break;
            case 3:
                interfaceInserirCarro(estaci);
                break;
            case 4:
                interfaceRemoverCarro(estaci);
                break;
            case 5:
                if(estaci == NULL){
                    system("cls");
                    imprime_erro("ESTACIONAMENTO NÃO CONFIGURADO!");
                }
                break;
            case 0:
                printf("\n\n\nSaindo...\n\n");
                exit(0);
                break;
            default:
                system("cls");
                imprime_erro("ESCOLHA INVÁLIDA TENTE NOVAMENTE.");
                break;
        }
    }
}

Estacionamento* interfaceConfigurarEstacionamento(Estacionamento *estaci){


    system("cls");

    mudar_cor(1);
    printf("\n\n              CONFIGURAR ESTACIONAMENTO");
    printf("\n-------------------------------------------------\n\n");


    int maxRua,qtdFileiras,maxFileiras;

    mudar_cor(3);
    printf("\nQual quantide de fileira que o estacionamento deve ter? ");
    scanf("%d", &qtdFileiras);

    printf("\nQual quantide máxima de carro por fileiras? ");
    scanf("%d", &maxFileiras);

    printf("\nRecomendamos que tenha pelo menos %d espaços na rua.", maxFileiras - 1);
    printf("\nQual quantidade máxima de carros na rua? ");
    scanf("%d", &maxRua);
    cor_padrao();

    estaci = criar_estacionamento(abs(qtdFileiras), abs(maxFileiras), abs(maxRua));

    if(estaci == NULL){

        system("cls");
        imprime_erro("ERRO!MEMORIA INSUFICIENTE, FECHE ALGUM PROCESSO E TENTE NOVAMENTE.\n\n");
        system("pause");
        exit(0);

    }

    system("cls");

    return estaci;

}

void interfaceInserirCarro(Estacionamento *estaci){

     system("cls");

     mudar_cor(1);
     printf("\n\n              INSERIR CARRO");
     printf("\n-------------------------------------------------\n\n");

     if(estaci == NULL){
        system("cls");
        imprime_erro("ESTACIONAMENTO NÃO CONFIGURADO, CONFIGURE UM ANTES DE CONTINUAR.");

     }else{

        Carro *carro = NULL;

        int previsaoSaida, fileira, resultado;
        char *placa = NULL;



        mudar_cor(3);

        placa = capturar_placa();

        printf("\nQuanto tempo ele irá permanecer no estacionamento(em horas)? ");
        scanf("%d", &previsaoSaida);

        carro = criar_carro(placa, abs(previsaoSaida));

        if(carro == NULL){

            system("cls");
            imprime_erro("ERRO AO ALOCAR MEMORIA, PORFAVOR FECHE ALGUM PROCESSO E TENTE NOVAMENTE.");

        }else{

            char resposta;

            fileira = procurar_vaga(estaci, carro);


            do{
                mudar_cor(3);
                printf("\nDeseja colocar o veiculo nessa posição(S/N)? ");

                resposta = getch();

                resposta = tolower(resposta);


                switch(resposta){
                    case 's':
                        resultado = inserir_carro(estaci, carro, fileira);
                        if(resultado == 1){

                            system("cls");
                            imprime_sucesso("\nVEICULO INSERIDO AO ESTACIONAMENTO COM SUCESSO.\n");

                        }else{

                            system("cls");
                            imprime_erro("ESTACIONAMENTO CHEIO.");
                        }
                        break;
                    case 'n':
                        do{
                          mudar_cor(3);
                          printf("\n\nDeseja inserir veiculo em qual fileira? ");
                          scanf("%d", &fileira);

                          resultado = inserir_carro(estaci, carro, (fileira - 1));

                          if(resultado == 1){

                             system("cls");
                             imprime_sucesso("\nVEICULO INSERIDO AO ESTACIONAMENTO COM SUCESSO.\n");

                          }else{

                             imprime_erro("\nFILEIRA INVALIDA OU CHEIA.");
                          }

                        }while(resultado == -1);

                        break;
                    default:
                        imprime_erro("\nRESPOSTA INVALIDA.\n");
                        break;
                }

                }while(resposta != 's' && resposta != 'n');


        }

     }

     cor_padrao();
}

void interfaceRemoverCarro(Estacionamento *estaci){

     system("cls");

     int resultado;
     char *placa = NULL;

     mudar_cor(1);
     printf("\n\n              REMOVER CARRO");
     printf("\n-------------------------------------------------\n\n");

     if(estaci == NULL){
        system("cls");
        imprime_erro("ESTACIONAMENTO NÃO CONFIGURADO, CONFIGURE UM ANTES DE CONTINUAR.");

     }else{

         mudar_cor(3);

         placa = capturar_placa();


         resultado = remover_carro(estaci, placa);

         if(resultado == -1){

            imprime_erro("CARRO NÃO ENCONTRADO.");

         }else{

            char msg[MSG_SIZE];

            sprintf(msg,"\nCARRO COM A PLACA %s FOI REMOVIDO COM SUCESSO.\n", placa);
            imprime_sucesso(msg);

         }

     }


}

char* capturar_placa(){

     char *placa = (char*)malloc(TAM_PLACA * sizeof(char));

     int validacao;

     do{
         mudar_cor(3);
         printf("\nDigite a placa do carro: ");

         fflush(stdin);

         fgets(placa, TAM_PLACA, stdin);

         validacao = validarPlaca(placa);

         if(validacao == -1){

            imprime_erro("PLACA COM FORMATO INCORRETO.");

         }

     }while(validacao == -1);

     return placa;
}

int validarPlaca(char* placa){

     if(strlen(placa) != (TAM_PLACA - 1)){

            return -1;
     }


    for(int i = 0; i < (TAM_PLACA - 1) ; i++){

        if(i < 3 && (placa[i] > 90 || placa[i] < 65)){

            return -1;

        }else if(i >= 3 && (placa[i] > 57 || placa[i] < 48)){

            return -1;

        }
    }

    return 1;

}





