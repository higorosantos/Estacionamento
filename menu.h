#include "utils.h"
#include "estacionamento.h"
#include <conio.h>

int interfaceMenuPrincipal();

void menuPrincipal();

void interfaceInserirCarro(Estacionamento *estaci);

void interfaceRemoverCarro(Estacionamento *estaci);

Estacionamento* interfaceConfigurarEstacionamento(Estacionamento *estaci);

char* capturar_placa();

int validarPlaca(char *placa);

void imprime_total(Estacionamento * estaci);
