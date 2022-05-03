#include "carro.h"

typedef struct _rua Rua;

typedef struct _no No;


Rua* cria_fila(int tam);

int insere_fila(Rua* rua, Carro *carro);

int remove_fila(Rua* rua);

int fila_vazia(Rua* rua);
