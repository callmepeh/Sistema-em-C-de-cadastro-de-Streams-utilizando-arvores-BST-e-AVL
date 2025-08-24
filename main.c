#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "arvore.h"

int main(){
    Categorias *c = criaCategoria(ENTRETENIMENTO, "Terror");
    printf("%s - %d\n", c->nome, c->tipo);

    Apresentador *a = criaApresentador("Brenda", "Terror", "Mubi");
    printf("%s - %s - %s\n", a->nome, a->nomeCategoriaAtual, a->nomeStreamAtual);
    printf("Antigas(quant: %d): %s - inicio: %d/%d/%d - fim: %d/%d/%d\n", a->quantidadeStAntigas, a->stAntigas->nome, a->stAntigas->inicio.dia, a->stAntigas->inicio.mes, a->stAntigas->inicio.ano, a->stAntigas->fim.dia, a->stAntigas->fim.mes, a->stAntigas->fim.ano);
    return 0;
}

//Para rodar: gcc main.c lista.c arvore.c -o programa
//            ./programa


//Teste funções criaCategoria e criaApresentador 

/*

 Categorias *c = criaCategoria(ENTRETENIMENTO, "Terror");
    printf("%s - %d\n", c->nome, c->tipo);

    Apresentador *a = criaApresentador("Brenda", "Terror", "Mubi");
    printf("%s - %s - %s\n", a->nome, a->nomeCategoriaAtual, a->nomeStreamAtual);
    printf("Antigas(quant: %d): %s - inicio: %d/%d/%d - fim: %d/%d/%d\n", a->quantidadeStAntigas, a->stAntigas->nome, a->stAntigas->inicio.dia, a->stAntigas->inicio.mes, a->stAntigas->inicio.ano, a->stAntigas->fim.dia, a->stAntigas->fim.mes, a->stAntigas->fim.ano);

*/