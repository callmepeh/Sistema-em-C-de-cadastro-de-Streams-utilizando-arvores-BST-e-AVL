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

Categorias *alocarCategoria(Categorias *no){
    no = (Categorias *)malloc(sizeof(Categorias));
    return (!no)?NULL:no;
}

Apresentador *alocarApresentador(Apresentador *no){
    no = (Apresentador *)malloc(sizeof(Apresentador));
    return (!no)?NULL:no;
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

int ehFolha(Arvore *no){
    int i = 0;
    if(no->dir == NULL && no->esq == NULL) i = 1;
    return i;
}

Arvore *soUmFilho(Arvore *no){
    Arvore *filho = NULL;
    if(no->dir == NULL && no->esq) filho = no->esq;
    if(no->dir && no->esq == NULL) filho = no->dir;
    return filho;
}

Arvore *maiorAhEsquerda(Arvore *no){
    if(no->dir) maiorAhEsquerda(no->dir);
    return no;
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

        cmp_result = strcmp(nome_copia, raiz->dado.STREAM.nome);

        if ((cmp_result = strcmp(nome_copia, raiz->dado.STREAM.nome)) == 0) busca = raiz;
        else if ((cmp_result = strcmp(nome_copia, raiz->dado.STREAM.nome)) < 0) busca = buscarNaArvore(raiz->esq, nome_copia);
        else busca = buscarNaArvore(raiz->dir, nome_copia);
    }

    return busca;
}

int removerDaArvore(Arvore **arvore, Arvore *vaiSerRemovido){
    int remover = 0;
    if(*arvore){
        if(strcmp((*arvore)->dado.PROGRAMA.nome, vaiSerRemovido->dado.PROGRAMA.nome) < 0) remover = removerDaArvore(&((*arvore)->dir), vaiSerRemovido);
        else if(strcmp((*arvore)->dado.PROGRAMA.nome, vaiSerRemovido->dado.PROGRAMA.nome) > 0) remover = removerDaArvore(&((*arvore)->esq), vaiSerRemovido);
        else{
            remover = 1;
            Arvore *auxi;
            if(ehFolha(*arvore)){
                auxi = *arvore;
                *arvore = NULL;
                free(auxi);
            }else{
                Arvore *filho;
                if((filho = soUmFilho(*arvore))){
                    auxi = *arvore;
                    *arvore = filho;
                    free(auxi);
                }else{
                    auxi = maiorAhEsquerda((*arvore)->esq);
                    (*arvore)->dado = auxi->dado;
                    removerDaArvore(&((*arvore)->esq), auxi);
                }
            }
        }
    }

    return remover;
}

// LISTAS
Categorias *criaCategoria(TipoCategoria tipoC, char *nomeC){
    Categorias *nova = alocarCategoria(nova);
    if(!nova) return NULL;

    char tempNomeC[50];
    strcpy(tempNomeC, nomeC);
    deixaMaiuscula(tempNomeC);
    strcpy(nova->nome, tempNomeC);

    nova->tipo = tipoC;
    nova->programa = NULL;
    nova->prox = NULL;

    return nova;
}

void encerraST(Apresentador **ap){
    struct tm *infoTempoLocal = tempoAtual();
    (*ap)->stAntigas[(*ap)->quantidadeStAntigas - 1].fim.dia = infoTempoLocal->tm_mday;
    (*ap)->stAntigas[(*ap)->quantidadeStAntigas - 1].fim.mes = infoTempoLocal->tm_mon + 1;
    (*ap)->stAntigas[(*ap)->quantidadeStAntigas - 1].fim.ano = infoTempoLocal->tm_year + 1900;

    strcpy((*ap)->nomeStreamAtual, " ");
    strcpy((*ap)->nomeCategoriaAtual, " ");
}

void iniciaST(Apresentador **p){
    (*p)->quantidadeStAntigas += 1;
    struct tm *infoTempoLocal = tempoAtual();

    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].inicio.dia = infoTempoLocal->tm_mday;
    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].inicio.mes = infoTempoLocal->tm_mon + 1;
    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].inicio.ano = infoTempoLocal->tm_year + 1900;

    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].fim.dia = 0;
    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].fim.mes = 0;
    (*p)->stAntigas[(*p)->quantidadeStAntigas - 1].fim.ano = 0;
}

Apresentador *criaApresentador(char *nome, char *nomeCA, char *nomeST){
    Apresentador *novo = alocarApresentador(novo); 
    if(!novo) return NULL;
    novo->stAntigas = (StreamsAntigas *)malloc(sizeof(StreamsAntigas)); 
    if(!novo->stAntigas) return NULL;

    char tempNome[50], tempNomeST[50];

    strcpy(tempNome, nome); deixaMaiuscula(tempNome);
    strcpy(novo->nome, tempNome);

    strcpy(tempNome, nomeCA); deixaMaiuscula(tempNome);
    strcpy(novo->nomeCategoriaAtual, tempNome);

    strcpy(tempNomeST, nomeST); deixaMaiuscula(tempNomeST);
    strcpy(novo->nomeStreamAtual, tempNomeST);

    novo->quantidadeStAntigas = 1;
    strcpy(novo->stAntigas[novo->quantidadeStAntigas - 1].nome, tempNomeST);

    iniciaST(&novo);

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

Categorias *buscaERetornaCategoria(Categorias *lista, char *nome){
    Categorias *atual = lista, *busca = NULL;
    do{
        if(strcmp(atual->nome, nome) == 0) busca = atual;
        atual = atual->prox;
    }while(atual != lista);

    return busca;
}

int cadastrarCategoria(Categorias *nova, char *nomeST, Arvore *arvST){
    int cadastrou = 0;
    Arvore *stream = buscarNaArvore(arvST, nomeST);
        if(stream){

            Categorias **lista = &(stream->dado.STREAM.categorias);

            if(*lista){  
                if(existeCategoria(*lista, nova->nome) == 0){
                    cadastrou = 1;

                    Categorias *anterior = stream->dado.STREAM.categorias;
                    Categorias *proximo = stream->dado.STREAM.categorias->prox;

                    if (strcmp(nova->nome, anterior->nome) < 0) {
                        while (proximo != stream->dado.STREAM.categorias) proximo = proximo->prox;
                        
                        proximo->prox = nova;
                        nova->prox = anterior;
                        stream->dado.STREAM.categorias = nova;
                    } else {
                        while (proximo != stream->dado.STREAM.categorias && strcmp(nova->nome, proximo->nome) >= 0) {
                            anterior = proximo;
                            proximo = proximo->prox;
                        }
                        if(strcmp(proximo->nome, stream->dado.STREAM.categorias->nome) == 0){
                            anterior->prox = nova;
                            nova->prox = stream->dado.STREAM.categorias;
                        }else{
                            anterior->prox = nova;
                            nova->prox = proximo;
                        }
                    }
                }
            }else{
                cadastrou = 1;
                stream->dado.STREAM.categorias = nova;
                nova->prox = nova;
            }
        }

        return cadastrou;
}

int existeApresentador(Apresentador *lista, char *nome){
    int i = 0;
    if(lista){
        if(strcmp(lista->nome, nome) == 0) i = 1;
        i = existeApresentador(lista->prox, nome);
    }

    return i;
}

Apresentador *buscaApresentador(Apresentador *lista, char *nome){
    Apresentador *busca = NULL;
    if(lista){
        if(strcmp(lista->nome, nome) == 0) busca = lista;
        busca = existeApresentador(lista->prox, nome);
    }

    return busca;
}

int inserirApresentadorOrdenado(Apresentador **lista, Apresentador *novo){
    int inseriu = 0;
    if(*lista){
        if(strcmp(novo->nome, (*lista)->nome) < 0){
            novo->prox = *lista;
            (*lista)->ant = novo;
            *lista = novo;
            inseriu = 1;
        }else{
            Apresentador *atual = *lista, *ant = NULL;
            while(atual && (strcmp(novo->nome, atual->nome)) > 0){
                ant = atual;
                atual = atual->prox;
            }
            if(strcmp(novo->nome, atual->nome) != 0){
                inseriu = 1;
                if(atual){
                    ant->prox = novo;
                    novo->ant = ant;
                    atual->ant = novo;
                    novo->prox = atual;
                }else{
                    ant->prox = novo;
                    novo->ant = ant;
                }    
            }
        }
    }

    return inseriu;
}

int cadastrarApresentador(Apresentador *novo, Arvore *arvST, Apresentador *listaAP){
    int cadastrar;
    if(existeApresentador(listaAP, novo->nome) == 0){
        Arvore *stream = buscarNaArvore(arvST, novo->nomeStreamAtual);
        if(stream){
            cadastrar = inserirApresentadorOrdenado(&listaAP, novo);
        }
    }

    return cadastrar;
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

int removerProgramaDeCateDeST(Arvore *arvST, char *nomeST, char *nomeCateg, char *nomeProg){
    int i = 0;
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if(stream){
        Categorias *lista = buscaCategoria(stream->dado.STREAM.categorias, nomeCateg);
        if(lista){
            if(lista->programa){
                Arvore *programa = buscarNaArvore(lista->programa, nomeProg);
                if(programa){
                    i = removerDaArvore(&(lista->programa), programa);
                }
            }
        } 
    }

    return i;
}

Categorias *removerCategoria(Categorias *lista, Categorias *no){
    if(lista == lista->prox){
        free(lista);
        return NULL;
    }else{
        Categorias *atual = lista;
        Categorias *ant = NULL;

        do{
            if((strcmp(atual->nome, no->nome)) == 0){
                if((strcmp(atual->nome, lista->nome)) == 0){
                    Categorias *aux = lista;
                    while(aux->prox != lista) aux = aux->prox;
                    aux->prox = lista->prox;
                    Categorias *novaCabeca = lista->prox;
                    free(lista);
                    return novaCabeca;
                }
                ant->prox = atual->prox;
                free(atual);
                return lista;
            }
            ant = atual;
            atual = atual->prox;
        }while(atual != lista);
    }
    return lista;
}

int removerCategDeST(Arvore *arvST, char *nomeST, char *nomeCateg){
    int removeu = 0;
    Arvore *stream = buscarNaArvore(arvST, nomeST);

    if(stream){
        Categorias *lista = stream->dado.STREAM.categorias;
        if(lista){
            Categorias *categoria = buscaCategoria(lista, nomeCateg);
            if(categoria){
                if(categoria->programa == NULL){
                    removeu = 1;
                    lista = removerCategoria(lista, categoria);
                }
            }
        }
    }

}

// AUXILIA FUNÇÕES DE ALTERAR

Arvore *existeApresentadorEmPrograma(Arvore *programa, char *nomeAP){
    Arvore *busca = NULL;
    if(programa){
        if(strcmp(programa->dado.PROGRAMA.NomeApresentador, nomeAP) == 0) busca = programa;
        else{
            verificaSeExisteApEmST(programa->esq, nomeAP);
            verificaSeExisteApEmST(programa->dir, nomeAP);
        }
    }

    return busca;
}

Categorias *existeApresentadorEmCategorias(Categorias *lista, char *nomeAP, Arvore **res){
    Categorias *atual = lista, *ant = NULL;
    if(lista){
        do{
            *res = existeApresentadorEmPrograma(atual->programa, nomeAP);
            ant = atual;
            atual = atual->prox;
        }while(atual != lista && res == NULL);
    }

    return ant;
    
}

// ALTERAR REMOVENDO O PROGRAMA ANTIGO DO APRESENTADOR

int *alterarStreamDeApresentador_removePrograma(Arvore *streams, Apresentador *apresentador, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma){
    int i = 0;
    // Pega a Stream atual e nova do apresentador
    Arvore *atualST = buscarNaArvore(streams, apresentador->nomeStreamAtual);
    Arvore *novaST = buscarNaArvore(streams, nomeNovaStream);

    // Só começa a alterar se as streams não forem nulas nem iguais
    if((atualST && novaST) && strcmp(atualST->dado.STREAM.nome, novaST->dado.STREAM.nome) != 0){
        
        // Verifica se o apresentador já está na nova Stream
        Categorias *CTnova = novaST->dado.STREAM.categorias;
        Arvore *res = NULL;
        Categorias *cat = existeApresentadorEmCategorias(CTnova, apresentador->nome, &res);
        // res = o programa do apresentador ou nulo | cat = a categoria que guarda a árvore de programas do programa em res

        // Só começa a alterar se res == NULL
        if(!res){

            // Verifica se a categoria que o apresentador vai entrar na nova Stream existe
            int j = existeCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);

            // Se existe
            if(j){
                Categorias *auxi;
                // EcerraST = coloca a data de término na Stream no vetor de Streams antigas e remove programa atual da stream
                encerraST(&apresentador);
                res = NULL;
                cat = existeApresentadorEmCategorias(atualST->dado.STREAM.categorias, apresentador->nome, &res); 
                removerDaArvore(&(cat->programa), res);

                // Aloca memória no vetor de stream antigas para a nova stream (só registra a data de início lá e o nome, data de fim é zerada)
                apresentador->stAntigas = (StreamsAntigas *)realloc(apresentador->stAntigas, apresentador->quantidadeStAntigas * sizeof(StreamsAntigas));
                strcpy(apresentador->stAntigas[apresentador->quantidadeStAntigas - 1].nome, novaST->dado.STREAM.nome);
                iniciaST(&apresentador);
                strcpy(apresentador->nomeStreamAtual, novaST->dado.STREAM.nome);
                
                // Insere o novo programa na nova Stream
                auxi = buscaERetornaCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);
                i = inserirArvBin(&(auxi->programa), novoPrograma);
            }
        }
    }

    return i;
}

// ALTERAR COLOCANDO OUTRO APRESENTADR NO PROGRAMA ANTIGO DO APRESENTADOR

int *alterarStreamDeApresentador_substituiApresentadorPrograma(Arvore *streams, Apresentador *lista, Apresentador *apresentador, Apresentador *substituto, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma){
    int i = 0;
    // Pega a Stream atual e nova do apresentador
    Arvore *atualST = buscarNaArvore(streams, apresentador->nomeStreamAtual);
    Arvore *novaST = buscarNaArvore(streams, nomeNovaStream);

    // Só começa a alterar se as streams não forem nulas nem iguais
    if((atualST && novaST) && strcmp(atualST->dado.STREAM.nome, novaST->dado.STREAM.nome) != 0){
        
        // Verifica se o apresentador já está na nova Stream
        Categorias *CTnova = novaST->dado.STREAM.categorias;
        Arvore *res = NULL;
        Categorias *cat = existeApresentadorEmCategorias(CTnova, apresentador->nome, &res);
        // res = o programa do apresentador ou nulo | cat = a categoria que guarda a árvore de programas do programa em res

        // Só começa a alterar se res == NULL
        if(!res){

            // Verifica se a categoria que o apresentador vai entrar na nova Stream existe
            int j = existeCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);

            // Se existe
            if(j){
                Categorias *auxi;
                // Insere o apresentador substituto na lista de apresentadores
                int k = inserirApresentadorOrdenado(&lista, substituto);
                if(k){
                    // EcerraST = coloca a data de término na Stream no vetor de Streams antigas
                    encerraST(&apresentador);
                    res = NULL;
                    cat = existeApresentadorEmCategorias(atualST->dado.STREAM.categorias, apresentador->nome, &res); 

                    // Substitui apresentador do programa atual da stream
                    strcpy(res->dado.PROGRAMA.NomeApresentador, substituto->nome);
                    iniciaST(&substituto);
                    strcpy(substituto->nomeStreamAtual, atualST->dado.STREAM.nome);

                    // Aloca memória no vetor de stream antigas para a nova stream (só registra a data de início lá e o nome, data de fim é zerada)
                    apresentador->stAntigas = (StreamsAntigas *)realloc(apresentador->stAntigas, apresentador->quantidadeStAntigas * sizeof(StreamsAntigas));
                    strcpy(apresentador->stAntigas[apresentador->quantidadeStAntigas - 1].nome, novaST->dado.STREAM.nome);
                    iniciaST(&apresentador);
                    strcpy(apresentador->nomeStreamAtual, novaST->dado.STREAM.nome);
                    
                    // Insere o novo programa na nova Stream
                    auxi = buscaERetornaCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);
                    i = inserirArvBin(&(auxi->programa), novoPrograma);
                }
                
            }
        }
    }

    return i;
}

