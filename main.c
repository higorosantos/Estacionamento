
#include "menu.h"


int main()
{
    setlocale(LC_ALL,"portuguese");

    bem_vindo();
    Estacionamento *estaci = NULL;
    estaci = interfaceConfigurarEstacionamento(estaci);
    menuPrincipal(estaci);
}
