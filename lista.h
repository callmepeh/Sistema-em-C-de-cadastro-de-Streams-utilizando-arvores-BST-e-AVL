#ifndef LISTA_H
#define LISTA_H

#include <time.h>

// enums
typedef enum {NOTICIA, ENTRETENIMENTO, ESPORTE} TipoCategoria;

// structs principais
typedef struct categorias {
    TipoCategoria tipo;
    char nome[50];
    struct no *programa;   // referência pra arvore
    struct categorias *prox;
} Categorias;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct streamsAntigas {
    char nome[50];
    Data inicio, fim;
} StreamsAntigas;

typedef struct apresentador {
    char nome[50], nomeCategoriaAtual[50], nomeStreamAtual[50];
    StreamsAntigas *stAntigas;
    int quantidadeStAntigas;
    struct apresentador *prox, *ant;
} Apresentador;

// funções
Categorias *criaCategoria(TipoCategoria tipo, char *nome);
struct tm *tempoAtual();
Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST);

#endif
