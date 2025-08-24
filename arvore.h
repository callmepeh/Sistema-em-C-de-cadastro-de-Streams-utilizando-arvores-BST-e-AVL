#ifndef ARVORE_H
#define ARVORE_H

#include "lista.h"

typedef enum {STREAM, PROGRAMA} TipoDado;
typedef enum {DIARIO, SEMANAL, QUINZENAL, MENSAL} Periodicidade;
typedef enum {AO_VIVO, SOB_DEMANDA} TipoTransmissao;

typedef struct {
    char NomeStream[50];
    char Site[100];
    Categorias *categorias;
} Stream;

typedef struct{
    char NomePrograma[50];
    char NomeApresentador[50];
    Periodicidade periodicidade;
    int Tempo;
    char HorarioInicio[10];
    TipoTransmissao tipotransmissao;
} Programa;

typedef union {
    Stream stream;
    Programa programa;
} DadoUnion;

typedef struct no {
    TipoDado tipo;
    DadoUnion dado;
    struct no *esq, *dir;
} No;

// funções
No* criarNo(TipoDado tipo, DadoUnion dado);
Stream* criarStream(char* nome, char* site);
Stream* inserirStream(Stream* raiz, Stream* nova);
Stream* buscarStream(Stream* raiz, char* nome);
void mostrarStreams(Stream* raiz);

#endif

