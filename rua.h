#include "carro.h"

typedef struct _rua Rua;


Rua* cria_fila(int tam);

int insere_fila(Rua* rua, Carro *carro);

Carro* remove_fila(Rua* rua);

int fila_vazia(Rua* rua);
