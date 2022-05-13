#include "menu.h"


int interfaceMenuPrincipal(){


    int opcao;
    mudar_cor(1);
    printf("\n\n               ESTACIONAMENTO");
    printf("\n-------------------------------------------------");
    mudar_cor(11);
    printf("\n\n\t1. Mostrar estacionamento.");
    printf("\n\t2. Inserir carro.");
    printf("\n\t3. Remover carro.");
    printf("\n\t4. Remover passo a passo.");
    printf("\n\t0. Sair.");
    mudar_cor(3);
    printf("\n\n\tEntre com a opção desejada: ");
    scanf("%d", &opcao);
    return opcao;

}

int interfaceMenuAdicionar(){


    int opcao;
    mudar_cor(1);
    printf("\n\n               ESTACIONAMENTO");
    printf("\n-------------------------------------------------");
    mudar_cor(11);
    printf("\n\n\t1. Estacionar carro no local recomendado.");
    printf("\n\t2. Escolher uma fileira para estacionar o carro.");
    mudar_cor(3);
    printf("\n\n\tEntre com a opção desejada: ");
    scanf("%d", &opcao);
    return opcao;

}

//PARTE LOGICA DOS MENUS
void menuPrincipal(Estacionamento *estaci) {


    int opcao_menu = -1;
    while (opcao_menu != 0) {
        opcao_menu = interfaceMenuPrincipal();
        switch(opcao_menu) {
            case 1:
                system("cls");
                imprime_total(estaci);
                break;
            case 2:
                interfaceInserirCarro(estaci);
                menuAdicionar(estaci);
                break;
            case 3:
                interfaceRemoverCarro(estaci);
                break;
            case 4:
                interfaceRemoverCarroPausa(estaci);
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

void menuAdicionar(Estacionamento *estaci) {

    int opcao_menu = -1;
    while (opcao_menu != 0) {
        opcao_menu = interfaceMenuAdicionar();
        switch(opcao_menu) {
            case 1:
                //ESTACIONAR NO LOCAL RECOMENDADO
                break;
            case 2:
                //ESTACIONA NA FILEIRA Q A DILZA ESCOLHER
                break;
            case 0:
                printf("\n\n\nSaindo...\n\n");
                exit(0);
                break;
            default:
                system("cls");
                imprime_erro("\tESCOLHA INVÁLIDA TENTE NOVAMENTE.");
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
    printf("\n\tQual quantide de fileira que o estacionamento deve ter? ");
    scanf("%d", &qtdFileiras);

    printf("\n\tQual quantide máxima de carro por fileiras? ");
    scanf("%d", &maxFileiras);

    printf("\n\tQual quantidade máxima de carros na rua? ");
    scanf("%d", &maxRua);
    cor_padrao();

    estaci = criar_estacionamento(abs(qtdFileiras), abs(maxFileiras), abs(maxRua));

    if(estaci == NULL){

        system("cls");
        imprime_erro("\tERRO!MEMORIA INSUFICIENTE, FECHE ALGUM PROCESSO E TENTE NOVAMENTE.\n\n");
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
        imprime_erro("\tESTACIONAMENTO NÃO CONFIGURADO, CONFIGURE UM ANTES DE CONTINUAR.");

        return;

     }

     if(estaci->totalVagas == 0){

        imprime_erro("\tESTACIONAMENTO CHEIO.");

        return;

     }

     Carro *carro = NULL;

     int previsaoSaida, fileira, resultado;
     char *placa = NULL;

     mudar_cor(3);

     placa = capturar_placa();

     printf("\n\tQuanto tempo ele irá permanecer no estacionamento(em horas)? ");
     scanf("%d", &previsaoSaida);

     carro = criar_carro(placa, abs(previsaoSaida));

     if(carro == NULL){

        system("cls");
        imprime_erro("\tERRO AO ALOCAR MEMORIA, PORFAVOR FECHE ALGUM PROCESSO E TENTE NOVAMENTE.");

     }else{

         char resposta;

         fileira = procurar_vaga(estaci, carro);

         imprime_goiaba(estaci, fileira);

         do{
            mudar_cor(3);
            printf("\n\tDeseja colocar o veiculo nessa posição(S/N)? ");

            resposta = getch();

            resposta = tolower(resposta);


            switch(resposta){
                case 's':
                    resultado = inserir_carro(estaci, carro, fileira);
                    if(resultado == 1){
                        system("cls");
                        imprime_sucesso("\n\tVEICULO INSERIDO AO ESTACIONAMENTO COM SUCESSO.\n");

                    }else{

                        system("cls");
                        imprime_erro("\tESTACIONAMENTO CHEIO.");

                    }
                    break;
                case 'n':
                      do{
                          mudar_cor(3);
                          printf("\n\n\tDeseja inserir veiculo em qual fileira? ");
                          scanf("%d", &fileira);

                          resultado = inserir_carro(estaci, carro, (fileira - 1));

                          if(resultado == 1){

                             system("cls");
                             imprime_sucesso("\n\tVEICULO INSERIDO AO ESTACIONAMENTO COM SUCESSO.\n");

                          }else{

                             imprime_erro("\n\tFILEIRA INVALIDA OU CHEIA.");
                          }

                        }while(resultado == -1);
                    break;
                default:
                    imprime_erro("\n\tRESPOSTA INVALIDA.\n");
                    break;
                }

             }while(resposta != 's' && resposta != 'n');
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
        imprime_erro("\tESTACIONAMENTO NÃO CONFIGURADO, CONFIGURE UM ANTES DE CONTINUAR.");

     }else{

         mudar_cor(3);

         placa = capturar_placa();

         resultado = remover_carro(estaci, placa);

         if(resultado == -1){

            imprime_erro("\tCARRO NÃO ENCONTRADO.");

         }else{

            char msg[MSG_SIZE];

            sprintf(msg,"\n\tCARRO COM A PLACA %s FOI REMOVIDO COM SUCESSO.\n", placa);
            imprime_sucesso(msg);

         }

     }


}

void interfaceRemoverCarroPausa(Estacionamento *estaci){

     system("cls");

     int resultado;
     char *placa = NULL;

     mudar_cor(1);
     printf("\n\n              REMOVER CARRO");
     printf("\n-------------------------------------------------\n\n");

     if(estaci == NULL){
        system("cls");
        imprime_erro("\tESTACIONAMENTO NÃO CONFIGURADO, CONFIGURE UM ANTES DE CONTINUAR.");

     }else{

         mudar_cor(3);

         placa = capturar_placa();

         resultado = remover_carro_pausa(estaci, placa);

         if(resultado == -1){

            imprime_erro("\tCARRO NÃO ENCONTRADO.");

         }else{

            char msg[MSG_SIZE];

            sprintf(msg,"\n\tCARRO COM A PLACA %s FOI REMOVIDO COM SUCESSO.\n", placa);
            imprime_sucesso(msg);

         }

     }


}

char* capturar_placa(){

     char *placa = (char*)malloc(TAM_PLACA * sizeof(char));

     int validacao;

     do{
         mudar_cor(3);
         printf("\n\tDigite a placa do carro: ");

         fflush(stdin);

         fgets(placa, TAM_PLACA, stdin);

         validacao = validarPlaca(placa);

         if(validacao == -1){

            imprime_erro("\tPLACA COM FORMATO INCORRETO.");

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

void imprime_total(Estacionamento * estaci){
    if(estaci == NULL){
        system("cls");
        imprime_erro("\tESTACIONAMENTO NÃO CONFIGURADO!");
    }else{
        mudar_cor(1);
        printf("\n\t--- ESTACIONAMENTO - TOTAL DE VAGAS: %d ---\n\n", estaci->totalVagas);
        mudar_cor(3);
        imprime_estaci(estaci);
        imprime_rua(estaci);
    }
}

void bem_vindo(){
    mudar_cor(1);
    printf("\n\t ______________________________________________");
    printf("\n\t|                                              |");
    printf("\n\t|            BEM VINDO AO GERADOR DE           |");
    printf("\n\t|              ESTACIONAMENTO 1.0              |");
    printf("\n\t|______________________________________________|");
    printf("\n\n");
    aperte_enter();
    mudar_cor(3);
    printf("\n\t ______________________________________________");
    printf("\n\t|                                              |");
    printf("\n\t|  Para dar início ao programa é necessário    |");
    printf("\n\t|  que você crie o seu estacionamento.         |");
    printf("\n\t|  Neste processo será definido a quantidade   |");
    printf("\n\t|  de fileiras de vagas, quantos carro caberão |");
    printf("\n\t|  em cada uma e, por fim, a quantidade de     |");
    printf("\n\t|  vagas na rua, que serão usadas somente para |");
    printf("\n\t|  manobrar os carros, caso seja necessário    |");
    printf("\n\t|  no momento de retirar um dos veículos.      |");
    printf("\n\t|______________________________________________|");
    printf("\n\n");
    aperte_enter();

}

