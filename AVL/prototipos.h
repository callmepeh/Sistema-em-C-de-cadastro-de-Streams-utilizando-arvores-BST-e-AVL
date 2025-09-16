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
typedef enum {STREAM = 1, PROGRAMA} TipoDado;
typedef enum {NOTICIA = 1, ENTRETENIMENTO, ESPORTE} TipoCategoria;
typedef enum {DIARIO = 1, SEMANAL, QUINZENAL, MENSAL} Periodicidade;
typedef enum {AO_VIVO = 1, SOB_DEMANDA} TipoTransmissao;
typedef enum {REMOVER = 1, ALTERAR} ProgramaAtual;
typedef enum {DOMINGO = 1, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO} DiaSemana;

// STRUCTS E UNION PARA ÁRVORES
typedef struct {
    int dia, mes, ano;
    DiaSemana diasemana;
} Data;

typedef struct stream {
    char nome[50], Site[100];
    struct categorias *categorias;
} Stream;

typedef struct programa {
    char nome[50], NomeApresentador[50], HorarioInicio[10];
    int Tempo;
    Periodicidade periodicidade;
    TipoTransmissao tipotransmissao;
    Data data;
} Programa;

typedef union {
    struct stream STREAM;
    struct programa PROGRAMA;
} DadoUnion;

typedef struct arvore{
    TipoDado tipo;
    DadoUnion dado;
    int alt;
    struct arvore *esq, *dir;
}Arvore; 

// STRUCTS PARA LISTAS E VETOR
typedef struct categorias {
    TipoCategoria tipo;
    char nome[50];
    struct arvore *programa;
    struct categorias *prox;
} Categorias;

typedef struct streamsAntigas {
    char nome[50];
    Data inicio, fim;
} StreamsAntigas;

typedef struct apresentador {
    char nome[50], nomeCategoriaAtual[50], nomeStreamAtual[50];
    StreamsAntigas stAntigas[50];
    int quantidadeStAntigas;
    struct apresentador *prox, *ant;
} Apresentador;

// BALANCEAMENTO

int fatorBalanceamento(Arvore *no);
void rotacionaEsquerda(Arvore **no);
void rotacionaDireita(Arvore **no);
void balanceamento(Arvore **no);
void atualizaAltura(Arvore **raiz);

// UTILITÁRIOS
Arvore *inicializar();
Arvore *alocar(TipoDado tipo);
Categorias *alocarCategoria();
Apresentador *alocarApresentador();

void deixaMaiuscula(char *str);
struct tm *tempoAtual();

int ehFolha(Arvore *no);
Arvore *soUmFilho(Arvore *no);
Arvore *maiorAhEsquerda(Arvore *no, Arvore **paiMaior);

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
Categorias *existeApresentadorEmCategorias(Categorias *lista, char *nomeAP, Arvore **res);

// Apresentador
int validarApresentador(Apresentador *lista, char *nomeAp, char *nomeStream, char *nomeCategoria);
int cadastrarApresentador(Apresentador *novo, Arvore *arvST, Apresentador **listaAP);
int inserirApresentadorOrdenado(Apresentador **listaA, Apresentador *novo);
Apresentador *buscaApresentador(Apresentador *lista, char *nome);
Apresentador *criaApresentador(char *nome, char *nomeCat, char *nomeST);
int alterarStreamDeApresentador_removePrograma(Arvore *streams, Apresentador *apresentador, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma);
int alterarStreamDeApresentador_substituiApresentadorPrograma(Arvore *streams, Apresentador **lista, Apresentador *apresentador, Apresentador *substituto, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma);
void mostrarApresentadoresDeCategoria(Apresentador *lista, char *nomeCategoria);
void encerraST(Apresentador *ap);
void iniciaST(Apresentador *p);

// ÁRVORES
void preencherDado(TipoDado tipo, Arvore *novoNo);
int inserirArvBin(Arvore **R, Arvore *novono);
void imprimirArvore(Arvore *raiz);
Arvore* buscarNaArvore(Arvore *raiz, char *nome);
int removerDaArvore(Arvore **arvore, Arvore *vaiSerRemovido);

// Streams
void mostrarStsQueTemCategoria(char *nomeCateg, Arvore *arvST);
void imprimeStreamsPorCategoria(Arvore *arvST, TipoCategoria tipo);
void mostrarApresentadoresDeStream(Apresentador *lista, char *nomeST);

// Programas
void mostrarProgsDeCategDeST(char *nomeST, Arvore *arvST, char *nomeCateg);
int removerProgramaDeCateDeST(Arvore *arvST, char *nomeST, char *nomeCateg, char *nomeProg);
Arvore *existeApresentadorEmPrograma(Arvore *programa, char *nomeAP);
int compararDiaSemana(DiaSemana d1, DiaSemana d2);
void mostrarProgramasDeStreamPorDiaSemanaHorario(Arvore *arvST, char *nomeST, char *horario, DiaSemana dia);
void mostrarProgramasPorDiaSemana(Arvore *raiz, DiaSemana dia);
void mostrarProgramasDeCategoriaPorDiaSemana(Arvore *arvST, char *nomeST, char *nomeCateg, DiaSemana dia);
void mostrarDadosdeumProgramadeumaCategoriadeumaStream(Arvore *arvST, char *nomeST, char *nomeCateg, char *nomoProg);
void imprimiPGDiaHorario(Arvore *raiz, DiaSemana dia, char *horario);

#endif
