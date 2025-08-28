#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

struct programa;
struct categorias;
struct stream;
struct apresentador;

typedef enum {STREAM, PROGRAMA} TipoDado;
typedef enum {NOTICIA, ENTRETENIMENTO, ESPORTE} TipoCategoria;
typedef enum {DIARIO, SEMANAL, QUINZENAL, MENSAL} Periodicidade;
typedef enum {AO_VIVO, SOB_DEMANDA} TipoTransmissao;


typedef struct stream {
    char NomeStream[50], Site[100];
    struct categorias *categorias;
    struct stream *esq, *dir;
} Stream;

typedef struct programa {
    char NomePrograma[50], NomeApresentador[50], HorarioInicio[10];
    int Tempo;
    Periodicidade periodicidade;
    TipoTransmissao tipotransmissao;
    struct programa *esq, *dir;
} Programa;

typedef union {
    Stream stream;
    Programa programa;
} DadoUnion;

typedef struct No{
    TipoDado tipo;
    DadoUnion dado;
    struct No *esq, *dir;
}No; 

typedef struct categorias {
    TipoCategoria tipo;
    char nome[50];
    struct programa *programa;
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



void deixaMaiuscula(char *str);
struct tm *tempoAtual();

Categorias *criaCategoria(TipoCategoria tipo, char *nome);
Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST);

int existeCategoria(Categorias *lista, char *nome);
void cadastrarCategoria(Categorias *nova, char *nomeST, Stream *arvST);

int existeApresentador(Apresentador *lista, char *nome);
void inserirApresentadorOrdenado(Apresentador **listaA, Apresentador *novo);
void cadastrarApresentador(Apresentador *novo, Stream *arvST, Apresentador *listaAP);

void mostrarCategoriasDeST(char *nomeST);
Categorias *buscaCategoria(Categoria *lista, char *nome);
void mostrarProgsDeCategDeST(char *nomeST, Stream *arvST, char *nomeCateg);
void mostrarStsQueTemCategoria(char *nomeCateg, Stream *arvST);

No* criarNo(TipoDado tipo);
int inserirArvBin(No **R, No *novono);
void imprimirArvore(No *raiz);
//Stream* buscarStream(Stream *raiz, char *nome);
void mostrarStreams(Stream *raiz);

#endif
