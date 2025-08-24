#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"
#include "arvore.h"

Categorias *criaCategoria(TipoCategoria tipoC, char *nomeC){
    Categorias *nova = (Categorias *)malloc(sizeof(Categorias));

    nova->tipo = tipoC;
    strcpy(nova->nome, nomeC);
    nova->programa = NULL;
    nova->prox = NULL;

    return nova;
}

struct tm *tempoAtual(){
    time_t agora;
    time(&agora);

    struct tm *infoTempoLocal;
    infoTempoLocal = localtime(&agora);

    return infoTempoLocal;
}

Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST){
    Apresentador *novo = (Apresentador *)malloc(sizeof(Apresentador));

    strcpy(novo->nome, nome);
    strcpy(novo->nomeCategoriaAtual, nomeCA);
    strcpy(novo->nomeStreamAtual, nomeST);
    novo->quantidadeStAntigas = 1;

    novo->stAntigas = (StreamsAntigas *)malloc(sizeof(StreamsAntigas));
    strcpy(novo->stAntigas->nome, nomeST);

    struct tm *infoTempoLocal = tempoAtual();

    novo->stAntigas->inicio.dia = infoTempoLocal->tm_mday;
    novo->stAntigas->inicio.mes = infoTempoLocal->tm_mon + 1;
    novo->stAntigas->inicio.ano = infoTempoLocal->tm_year + 1900;

    novo->stAntigas->fim.dia = 0;
    novo->stAntigas->fim.mes = 0;
    novo->stAntigas->fim.ano = 0;

    novo->prox = novo->ant = NULL;

    return novo;
}