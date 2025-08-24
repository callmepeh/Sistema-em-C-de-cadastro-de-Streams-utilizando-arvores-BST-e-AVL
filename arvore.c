#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "lista.h"

No* criarNo(TipoDado tipo, DadoUnion dado) {
    No* novo = (No*) malloc(sizeof(No));
    novo->tipo = tipo;
    novo->dado = dado;
    novo->esq = novo->dir = NULL;
    return novo;
}