#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "utils.h"
#include "estacionamento.h"


int interfaceMenuPrincipal();

void menuPrincipal();

void interfaceInserirCarro(Estacionamento *estaci);

void interfaceRemoverCarro(Estacionamento *estaci);

Estacionamento* interfaceConfigurarEstacionamento(Estacionamento *estaci);

char* capturar_placa();

int validarPlaca(char *placa);

void imprime_total(Estacionamento * estaci);

void bem_vindo();
