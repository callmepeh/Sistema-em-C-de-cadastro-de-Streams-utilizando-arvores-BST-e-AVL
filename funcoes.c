#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "prototipos.h"

// UTILITÁRIOS
Arvore *inicializar(){
    return NULL;
}

Arvore *alocar(Arvore *arv, TipoDado tipo){
    arv = (Arvore *)malloc(sizeof(Arvore));
    if(!arv) return NULL;
    arv->tipo = tipo;
    arv->esq = arv->dir = NULL;
    return arv;
}

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

// ÁRVORE
void *preencherDado(TipoDado tipo, Arvore **novoNo) {
    char auxi[50];

    if (tipo == STREAM) {
        printf("Digite o nome da stream: ");
        scanf(" %[^\n]", auxi);
        deixaMaiuscula(auxi);
        strcpy((*novoNo)->dado.STREAM.nome, auxi);

        printf("Digite o site: ");
        scanf(" %[^\n]", (*novoNo)->dado.STREAM.Site);

        (*novoNo)->dado.STREAM.categorias = NULL;
    }
    else if (tipo == PROGRAMA) {
        printf("Digite o nome do programa: ");
        scanf(" %[^\n]", auxi);
        deixaMaiuscula(auxi);
        strcpy((*novoNo)->dado.PROGRAMA.nome, auxi);

        printf("Digite o nome do apresentador: ");
        scanf(" %[^\n]", (*novoNo)->dado.PROGRAMA.NomeApresentador);

        printf("Digite o horário de início (HH:MM): ");
        scanf(" %[^\n]", (*novoNo)->dado.PROGRAMA.HorarioInicio);

        printf("Digite o tempo (em minutos): ");
        scanf("%d", &((*novoNo)->dado.PROGRAMA.Tempo));
    }
}

int inserirArvBin(Arvore **R, Arvore *novono) {
    int inseriu = 0;
    if (*R == NULL) {
        *R = novono;
        inseriu = 1;
    }else{
        if (strcmp(novono->dado.STREAM.nome, (*R)->dado.STREAM.nome) < 0) inseriu = inserirArvBin(&((*R)->esq), novono);
        else if (strcmp(novono->dado.STREAM.nome, (*R)->dado.STREAM.nome) > 0) inseriu = inserirArvBin(&((*R)->dir), novono);
    }
    
    return inseriu;
}

void imprimirArvore(Arvore *raiz) {
    if(raiz){
        imprimirArvore(raiz->esq);
        if (raiz->tipo == STREAM) printf("[STREAM] Nome: %s | Site: %s\n", raiz->dado.STREAM.nome, raiz->dado.STREAM.Site);
        else {
            printf("[PROGRAMA] Nome: %s | Apresentador: %s | Inicio: %s | Tempo: %d\n",
                raiz->dado.PROGRAMA.nome,
                raiz->dado.PROGRAMA.NomeApresentador,
                raiz->dado.PROGRAMA.HorarioInicio,
                raiz->dado.PROGRAMA.Tempo);
        }
        imprimirArvore(raiz->dir); 
    }
}

Arvore* buscarNaArvore(Arvore *raiz, char *nome){
    Arvore *busca = NULL;
    if(raiz){
        char nome_copia[50];
        strcpy(nome_copia, nome);
        deixaMaiuscula(nome_copia);
        int cmp_result;

        if (raiz->tipo == STREAM) cmp_result = strcmp(nome_copia, raiz->dado.STREAM.nome);
        else if (raiz->tipo == PROGRAMA) cmp_result = strcmp(nome_copia, raiz->dado.PROGRAMA.nome);
        else return NULL; // Tipo de dado desconhecido

        if ((cmp_result = strcmp(nome_copia, raiz->dado.STREAM.nome)) == 0) busca = raiz;
        else if ((cmp_result = strcmp(nome_copia, raiz->dado.PROGRAMA.nome)) < 0) busca = buscarNaArvore(raiz->esq, nome_copia);
        else busca = buscarNaArvore(raiz->dir, nome_copia);
    }

    return busca;
}

// LISTAS
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


void cadastrarCategoria(Categorias *nova, char *nomeST, Arvore *arvST){
    Arvore *stream = buscarNaArvore(arvST, nomeST);
        if(stream){

            Categorias *lista = stream->dado.STREAM.categorias;

            if(lista){  
                if(existeCategoria(lista, nova->nome) == 0){

                    Categorias *anterior = stream->dado.STREAM.categorias;
                    Categorias *proximo = stream->dado.STREAM.categorias->prox;

                    if (strcmp(nova->nome, anterior->nome) < 0) {
                        while (proximo != stream->dado.STREAM.categorias) proximo = proximo->prox;
                        
                        proximo->prox = nova;
                        nova->prox = anterior;
                        stream->dado.STREAM.categorias = nova;
                    } else {
                        while (proximo != stream->dado.STREAM.categorias && strcmp(nova->nome, proximo->nome) > 0) {
                            anterior = proximo;
                            proximo = proximo->prox;
                        }
                        anterior->prox = nova;
                        nova->prox = proximo;
                    }
                }
            }else{
                stream->dado.STREAM.categorias = nova;
                nova->prox = nova;
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
            novo->prox = *lista;
            (*lista)->ant->prox = novo;
            novo->ant = (*lista)->ant;
            (*lista)->ant = novo;
        }else{
            inserirApresentadorOrdenado(&((*lista)->prox), novo);
        }
    }
}

void cadastrarApresentador(Apresentador *novo, Arvore *arvST, Apresentador *listaAP){
    if(existeApresentador(listaAP, novo->nome) == 0){
        Arvore *stream = buscarNaArvore(arvST, novo->nomeStreamAtual);
        if(stream){
            inserirApresentadorOrdenado(&listaAP, novo);
        }
    }
}

// FUNÇÕES DE MOSTRAR/REMOVER DE LISTAS E FUNÇÕES
// Precisa testar td abaixo

void mostrarCategoriasDeST(char *nome, Arvore *arvST){
    Arvore *stream = buscarNaArvore(arvST, nome);
    if(stream){
        if(stream->dado.STREAM.categorias){
            Categorias *atual = stream->dado.STREAM.categorias;
            do{
                printf("%s\n%d\n", atual->nome, atual->tipo);
                atual = atual->prox;
            }while(atual != stream->dado.STREAM.categorias);
        }
    }
}

Categorias *buscaCategoria(Categorias *lista, char *nome){
    Categorias *atual = lista, *i = NULL;
    if(atual){
        do{
            if(strcmp(atual->nome, nome) == 0) i = atual;
            atual = atual->prox;
        }while(atual != lista); 
    }

    return i;
}

void mostrarProgsDeCategDeST(char *nomeST, Arvore *arvST, char *nomeCateg){
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if(stream){
        if(existeCategoria(stream->dado.STREAM.categorias, nomeCateg)){
            Categorias *categoria = buscaCategoria(stream->dado.STREAM.categorias, nomeCateg);
            imprimirArvore(categoria->programa);
        }
    }
}

void mostrarStsQueTemCategoria(char *nomeCateg, Arvore *arvST){
    if(arvST){
        mostrarStsQueTemCategoria(nomeCateg, arvST->esq);
        if(existeCategoria(arvST->dado.STREAM.categorias, nomeCateg)){
            printf("Nome: %s\nSite: %s\n", arvST->dado.STREAM.nome, arvST->dado.STREAM.Site);
        }
        mostrarStsQueTemCategoria(nomeCateg, arvST->dir);
    }
}