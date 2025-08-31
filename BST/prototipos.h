#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#include <time.h>

// PRÉ DEFINIÇÕES DE STRUCTS
struct programa;
struct categorias;
struct stream;
struct apresentador;
struct arvore;

// ENUMS
typedef enum {STREAM, PROGRAMA} TipoDado;
typedef enum {NOTICIA, ENTRETENIMENTO, ESPORTE} TipoCategoria;
typedef enum {DIARIO, SEMANAL, QUINZENAL, MENSAL} Periodicidade;
typedef enum {AO_VIVO, SOB_DEMANDA} TipoTransmissao;
typedef enum {REMOVER, ALTERAR} ProgramaAtual;

// STRUCTS E UNION PARA ÁRVORES
typedef struct stream {
    char nome[50], Site[100];
    struct categorias *categorias;
} Stream;

typedef struct programa {
    char nome[50], NomeApresentador[50], HorarioInicio[10];
    int Tempo;
    Periodicidade periodicidade;
    TipoTransmissao tipotransmissao;
} Programa;

typedef union {
    struct stream STREAM;
    struct programa PROGRAMA;
} DadoUnion;

typedef struct arvore{
    TipoDado tipo;
    DadoUnion dado;
    struct arvore *esq, *dir;
}Arvore; 

// STRUCTS PARA LISTAS E VETOR
typedef struct categorias {
    TipoCategoria tipo;
    char nome[50];
    struct arvore *programa;
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

// UTILITÁRIOS
void deixaMaiuscula(char *str);
struct tm *tempoAtual();
Arvore *inicializar();
Arvore *alocar(Arvore *arv, TipoDado tipo);
Categorias *alocarCategoria(Categorias *no);
Apresentador *alocarApresentador(Apresentador *no);
int ehFolha(Arvore *no);
Arvore *soUmFilho(Arvore *no);
Arvore *maiorAhEsquerda(Arvore *no);
int existeCategoria(Categorias *lista, char *nome);
int existeApresentador(Apresentador *lista, char *nome);

// LISTAS
// Categorias
Categorias *criaCategoria(TipoCategoria tipo, char *nome);
int cadastrarCategoria(Categorias *nova, char *nomeST, Arvore *arvST);
Categorias *buscaCategoria(Categorias *lista, char *nome);
void mostrarCategoriasDeST(char *nomeST, Arvore *arvST);
Categorias *removerCategoria(Categorias *lista, Categorias *no);
int removerCategDeST(Arvore *arvST, char *nomeST, char *nomeCateg);

// Apresentador
int cadastrarApresentador(Apresentador *novo, Arvore *arvST, Apresentador *listaAP);
int inserirApresentadorOrdenado(Apresentador **listaA, Apresentador *novo);
Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST);

// ÁRVORES
void *preencherDado(TipoDado tipo, Arvore **novoNo);
int inserirArvBin(Arvore **R, Arvore *novono);
void imprimirArvore(Arvore *raiz);
Arvore* buscarNaArvore(Arvore *raiz, char *nome);
int removerDaArvore(Arvore **arvore, Arvore *vaiSerRemovido);

// Streams
void mostrarStsQueTemCategoria(char *nomeCateg, Arvore *arvST);

// Programas
void mostrarProgsDeCategDeST(char *nomeST, Arvore *arvST, char *nomeCateg);
int removerProgramaDeCateDeST(Arvore *arvST, char *nomeST, char *nomeCateg, char *nomeProg);

#endif
