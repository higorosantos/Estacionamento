#include "carro.h"

typedef struct _rua Rua;


Rua* criar_rua(int tam);

int inserir_rua(Rua* rua, Carro *carro);

Carro* remove_rua(Rua* rua);

int rua_vazia(Rua* rua);

void imprime_placa_rua(Rua *rua);

void imprime_tempo_rua(Rua *rua);

void imprime_espaco(Rua *rua);
