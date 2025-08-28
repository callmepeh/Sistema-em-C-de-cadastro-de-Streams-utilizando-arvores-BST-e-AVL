#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "prototipos.h"

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

No* criarNo(TipoDado tipo) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) return NULL;

    novo->tipo = tipo;
    novo->esq = novo->dir = NULL;

    if (tipo == STREAM) {
    
        printf("Digite o nome da stream: ");
        scanf(" %[^\n]", novo->dado.stream.NomeStream);

        printf("Digite o site: ");
        scanf(" %[^\n]", novo->dado.stream.Site);

        novo->dado.stream.categorias = NULL;
        novo->dado.stream.esq = novo->dado.stream.dir = NULL;
    }
    else if (tipo == PROGRAMA) {
    
        printf("Digite o nome do programa: ");
        scanf(" %[^\n]", novo->dado.programa.NomePrograma);

        printf("Digite o nome do apresentador: ");
        scanf(" %[^\n]", novo->dado.programa.NomeApresentador);

        printf("Digite o horário de início (HH:MM): ");
        scanf(" %[^\n]", novo->dado.programa.HorarioInicio);

        printf("Digite o tempo (em minutos): ");
        scanf("%d", &novo->dado.programa.Tempo);

        novo->dado.programa.esq = novo->dado.programa.dir = NULL;
    }

    return novo;
}

int inserirArvBin(No **R, No *novono) {
    if (*R == NULL) {
        *R = novono;
        return 1;
    }
    //  aqui é pra onde a gente passa o nome da stream ou do programa pra comparar fiz assim pq vi que é uma boa pra minuir codigo
    char chaveNovo[50], chaveRaiz[50];

    if (novono->tipo == STREAM) strcpy(chaveNovo, novono->dado.stream.NomeStream);
    else strcpy(chaveNovo, novono->dado.programa.NomePrograma);

    if ((*R)->tipo == STREAM) strcpy(chaveRaiz, (*R)->dado.stream.NomeStream);
    else strcpy(chaveRaiz, (*R)->dado.programa.NomePrograma);

    // insere normal
    if (strcmp(chaveNovo, chaveRaiz) < 0) return inserirArvBin(&(*R)->esq, novono);
    else return inserirArvBin(&(*R)->dir, novono);
}

void imprimirArvore(No *raiz) {
    if (raiz == NULL) return;

    imprimirArvore(raiz->esq);

    if (raiz->tipo == STREAM) {
        printf("[STREAM] Nome: %s | Site: %s\n", 
                raiz->dado.stream.NomeStream, 
                raiz->dado.stream.Site);
    } else {
        printf("[PROGRAMA] Nome: %s | Apresentador: %s | Inicio: %s | Tempo: %d\n",
                raiz->dado.programa.NomePrograma,
                raiz->dado.programa.NomeApresentador,
                raiz->dado.programa.HorarioInicio,
                raiz->dado.programa.Tempo);
    }

    imprimirArvore(raiz->dir);
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

int existeCategoria(Categorias *lista, char *nome){
    int i = 0;
    Categorias *cabeca = lista;
    do{
        if(strcmp(lista->nome, nome) == 0) i = 1;
        lista = lista->prox;
    }while(lista != cabeca);
    return i;
}


void cadastrarCategoria(Categorias *nova, char *nomeST, Stream *arvST){
    Stream *stream = buscarStream(arvST, nomeST);
        if(stream){

            Categorias *lista = stream->categorias;

            if(lista){  
                if(existeCategoria(lista, nova->nome) == 0){

                    Categorias *anterior = stream->categorias;
                    Categorias *proximo = stream->categorias->prox;

                    if (strcmp(nova->nome, anterior->nome) < 0) {
                        while (proximo != stream->categorias) proximo = proximo->prox;
                        
                        proximo->prox = nova;
                        nova->prox = anterior;
                        stream->categorias = nova;
                    } else {
                        while (proximo != stream->categorias && strcmp(nova->nome, proximo->nome) > 0) {
                            anterior = proximo;
                            proximo = proximo->prox;
                        }
                        anterior->prox = nova;
                        nova->prox = proximo;
                    }
                }else{
                    stream->categorias = nova;
                    nova->prox = nova;
                }
            }

        }
    
}

int existeApresentador(Apresentador *lista, char *nome){
    int i = 0;
    if(lista){
        if(strcmp(lista->nome, nome) == 0) i = 1;
        i = existeApresentador(lista->prox, nome);
    }

    return i;
}

void inserirApresentadorOrdenado(Apresentador **lista, Apresentador *novo){
    if(*lista){
        if(strcmp((*lista)->nome, novo->nome) > 0){
            novo->prox = lista;
            (*lista)->ant->prox = novo;
            novo->ant = (*lista)->ant;
            (*lista)->ant = novo;
        }else{
            inserirApresentadorOrdenado(&((*lista)->prox), novo);
        }
    }
}

void cadastrarApresentador(Apresentador *novo, Stream *arvST, Apresentador *listaAP){
    if(existeApresentador(listaAP, novo->nome) == 0){
        Stream *stream = buscarStream(arvST, novo->nomeStreamAtual);
        if(stream){
            inserirApresentadorOrdenado(&listaAP, novo);
        }
    }
}

// Precisa testar td abaixo

void mostrarCategoriasDeST(char *nome, Stream *arvST){
    Stream *stream = buscarStream(arvST, nome);
    if(stream){
        if(stream->categorias){
            Categoria *atual = stream->categorias;
            do{
                printf("%s\n%s\n", atual->nome, atual->tipo);
                atual = atual->prox;
            }while(atual != stream->categorias)
        }
    }
}

Categorias *buscaCategoria(Categoria *lista, char *nome){
    No *atual = lista, *i;
    if(!atual) i = NULL;
    else{
        do{
            if(strcmp(atual->nome, nome) == 0) strcpy(i, atual);
            atual->prox;
        }while(atual != lista);
    }

    return i;
}

void mostrarProgsDeCategDeST(char *nomeST, Stream *arvST, char *nomeCateg){
    Stream *stream = buscarStream(arvST, nome);
    if(stream){
        if(existeCategoria(stream->categorias, nomeCateg)){
            Programa *arvPro = buscaCategoria(stream->categorias, nomeCateg);
            imprimirArvore(arvPro);
        }
    }
}

void mostrarStsQueTemCategoria(char *nomeCateg, Stream *arvST){
    if(arvST){
        mostrarStsQueTemCategoria(char *nomeCateg, Stream *arvST->esq);
        if(existeCategoria(arvST->categorias, nomeCateg)){
            printf("Nome: %s\nSite: %s\n", arvST->NomeStream, arvST->Site);
        }
        mostrarStsQueTemCategoria(char *nomeCateg, Stream *arvST->dir);
    }
}