
#include "menu.h"


int main()
{
    setlocale(LC_ALL,"portuguese");

    bem_vindo();
    Estacionamento *estaci;
    estaci = interfaceConfigurarEstacionamento(estaci);
    menuPrincipal(estaci);
}
