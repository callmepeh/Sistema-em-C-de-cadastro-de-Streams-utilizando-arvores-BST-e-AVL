#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "lista.h"
#include "arvore.h"

void deixaMaiuscula(char *str){
    for(int i=0; str[i]!='\0'; i++) str[i] = toupper((unsigned char) str[i]);
}

struct tm *tempoAtual(){
    time_t agora;
    time(&agora);

    struct tm *infoTempoLocal;
    infoTempoLocal = localtime(&agora);

    return infoTempoLocal;
}

Categorias *criaCategoria(TipoCategoria tipoC, char *nomeC){
    Categorias *nova = (Categorias *)malloc(sizeof(Categorias));
    char tempNomeC[50];
    strcpy(tempNomeC, nomeC);

    nova->tipo = tipoC;
    deixaMaiuscula(tempNomeC);
    strcpy(nova->nome, tempNomeC);
    nova->programa = NULL;
    nova->prox = NULL;

    return nova;
}

Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST){
    Apresentador *novo = (Apresentador *)malloc(sizeof(Apresentador));
    char tempNome[50];
    char tempNomeCA[50];
    char tempNomeST[50];

    strcpy(tempNome, nome);
    deixaMaiuscula(tempNome);
    strcpy(novo->nome, tempNome);

    strcpy(tempNomeCA, nomeCA);
    deixaMaiuscula(tempNomeCA);
    strcpy(novo->nomeCategoriaAtual, tempNomeCA);

    strcpy(tempNomeST, nomeST);
    deixaMaiuscula(tempNomeST);
    strcpy(novo->nomeStreamAtual, tempNomeST);

    novo->quantidadeStAntigas = 1;

    novo->stAntigas = (StreamsAntigas *)malloc(sizeof(StreamsAntigas));
    strcpy(novo->stAntigas->nome, tempNomeST);

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

/*
void cadastrarCategoria(Categorias *nova, char *nomeST){
    //Chama um função de buscar stream na AB pelo nome que retorna NULL ou o nó da Stream
    //Busca na lista de streams da categoria pelo nome para ver se a 
}

*/