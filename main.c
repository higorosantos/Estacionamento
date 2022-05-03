#include <stdio.h>
#include <stdlib.h>
#include "fileira.h"

int main()
{
    printf("Helloworld!\n");

    Pilha *p = pilha_cria(4);

    int v;


    v = pilha_push(p, "4545", 24);
    v = pilha_push(p, "da5748", 4);
    v = pilha_push(p, "D7A784", 15);
    v = pilha_push(p, "d77a45", 35);

    return 0;
}
