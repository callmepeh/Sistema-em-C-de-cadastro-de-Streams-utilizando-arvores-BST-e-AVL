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

Arvore *alocar(TipoDado tipo){
    Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
    if(!arv) return NULL;
    arv->tipo = tipo;
    arv->esq = arv->dir = NULL;
    return arv;
}

Categorias *alocarCategoria(){
    Categorias *no = (Categorias *)malloc(sizeof(Categorias));
    if(!no) return NULL;
    no->prox = NULL;
    return no;
}

Apresentador *alocarApresentador(){
    Apresentador *no = (Apresentador *)malloc(sizeof(Apresentador));
    no->ant = no->prox = NULL;
    return no;
}

void deixaMaiuscula(char *str){
    for(int i=0; str[i]!='\0'; i++) str[i] = toupper((unsigned char) str[i]);
}

struct tm *tempoAtual(){
    time_t agora;
    time(&agora);

    struct tm *infoTempoLocal = malloc(sizeof(struct tm));  // aloca memória própria
    if(!infoTempoLocal) return NULL;

    struct tm *tmp = localtime(&agora);
    if(tmp) *infoTempoLocal = *tmp;  // copia o conteúdo
    else {
        free(infoTempoLocal);
        return NULL;
    }

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

Arvore *maiorAhEsquerda(Arvore *no, Arvore **paiMaior){
    Arvore *busca = no->esq;
    *paiMaior = no;
    while(busca->dir){
        *paiMaior = busca;
        busca = busca->dir;
    }
    return (*paiMaior)->dir;
 
}

int existeApresentador(Apresentador *lista, char *nome){
    deixaMaiuscula(nome);
    int i = 0;
    if(lista){
        if(strcmp(lista->nome, nome) == 0) i = 1;
        i = existeApresentador(lista->prox, nome);
    }

    return i;
}

Apresentador *buscaApresentador(Apresentador *lista, char *nome){
    char aux[50];
    strcpy(aux, nome);
    deixaMaiuscula(aux);
    Apresentador *busca = NULL, *atual = lista;
    while(atual){
        if(strcmp(atual->nome, aux) == 0) busca = atual;
        atual = atual->prox;
    }

    return busca;
}

int existeCategoria(Categorias *lista, char *nome){
    int i = 0;
    deixaMaiuscula(nome);
    Categorias *cabeca = lista;
    do{
        if(strcmp(lista->nome, nome) == 0) i = 1;
        lista = lista->prox;
    }while(lista != cabeca);
    return i;
}

Categorias *buscaERetornaCategoria(Categorias *lista, char *nome){
    Categorias *atual = lista, *busca = NULL;
    deixaMaiuscula(nome);
    do{
        if(strcmp(atual->nome, nome) == 0) busca = atual;
        atual = atual->prox;
    }while(atual != lista);

    return busca;
}


int validarApresentador(Apresentador *lista, char *nomeAp, char *nomeStream, char *nomeCategoria) {
    int i = 1;
    char auxAP[50], auxST[50], auxCT[50];
    strcpy(auxAP, nomeAp); deixaMaiuscula(auxAP);
    strcpy(auxST, nomeStream); deixaMaiuscula(auxST);
    strcpy(auxCT, nomeCategoria); deixaMaiuscula(auxCT);  // padroniza comparação
    Apresentador *ap = NULL;
    ap = buscaApresentador(lista, auxAP);

    if (ap){
        if (strcmp(ap->nomeStreamAtual, auxST) != 0) i = 0;
        if (strcmp(ap->nomeCategoriaAtual, auxCT) != 0) i = 0; 
    }else i = 0;
    
    return i;
}

// ÁRVORE
void preencherDado(TipoDado tipo, Arvore *novoNo){
    char auxi[50];

    if (tipo == STREAM) {
        printf("Digite o nome da stream: ");
        scanf(" %[^\n]", auxi);
        deixaMaiuscula(auxi);
        strcpy(novoNo->dado.STREAM.nome, auxi);

        printf("Digite o site: ");
        scanf(" %[^\n]", novoNo->dado.STREAM.Site);

        novoNo->dado.STREAM.categorias = NULL;
    }
    else if (tipo == PROGRAMA) {
        printf("Digite o nome do programa: ");
        scanf(" %[^\n]", auxi);
        deixaMaiuscula(auxi);
        strcpy(novoNo->dado.PROGRAMA.nome, auxi);

        printf("Digite o nome do apresentador: ");
        scanf(" %[^\n]", auxi);
        deixaMaiuscula(auxi);
        strcpy(novoNo->dado.PROGRAMA.NomeApresentador, auxi);

        printf("Digite a data da primeira transmissão do programa (DIA | MES | ANO): ");
        scanf("%d %d %d", &(novoNo->dado.PROGRAMA.data.dia), &(novoNo->dado.PROGRAMA.data.mes), &(novoNo->dado.PROGRAMA.data.ano)); printf("\n");

        int op = 0;
        while(op < 1 || op > 4){
            printf("Digite a periodicidade do programa - (1 - DIÁRIO | 2 - SEMANAL | 3 - QUINZENAL | 4- MENSAL): "); 
            scanf("%d", &op); printf("\n"); 
        }
        novoNo->dado.PROGRAMA.periodicidade = (Periodicidade) op;

        int opDia = 0;
        if (op != DIARIO){ 
            while(opDia < 1 || opDia > 8){
                printf("(1 - DOMINGO | 2 - SEGUNDA | 3 - TERÇA | 4- QUARTA | 5 - QUINTA | 6 - SEXTA | 7 - SÁBADO)\n");
                printf("Digite o dia da semana em que o programa é exibido: ");
                scanf("%d", &opDia); printf("\n"); 
            }
            
            novoNo->dado.PROGRAMA.data.diasemana = (DiaSemana) opDia;
        }

        printf("Digite o horário de início (HH:MM): ");
        scanf(" %[^\n]", novoNo->dado.PROGRAMA.HorarioInicio);

        printf("Digite o tempo (em minutos): ");
        scanf("%d", &(novoNo->dado.PROGRAMA.Tempo)); printf("\n");

        op = 0;
        while(op < 1 || op > 2){
            printf("Por último, informe o tipo de transissão do programa (1 - AO VIVO | 2 - SOB DEMANDA): ");
            scanf("%d", &op); printf("\n");
        }
        
        novoNo->dado.PROGRAMA.tipotransmissao = (TipoTransmissao) op; 

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
            }else{
                Arvore *filho;
                if((filho = soUmFilho(*arvore))){
                    auxi = *arvore;
                    *arvore = filho;
                }else{
                    Arvore *paiMaior = inicializar(), *noMaior = inicializar();
                    noMaior = maiorAhEsquerda(*arvore, &paiMaior);
                    (*arvore)->dado = noMaior->dado;
                    paiMaior->dir = noMaior->esq;
                    auxi = noMaior;
                }
            }
            free(auxi);
        }
    }

    return remover;
}

// LISTAS
Categorias *criaCategoria(TipoCategoria tipoC, char *nomeC){
    Categorias *nova = alocarCategoria();
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

void encerraST(Apresentador *ap){
        struct tm *infoTempoLocal = tempoAtual();
        ap->stAntigas[ap->quantidadeStAntigas - 1].fim.dia = infoTempoLocal->tm_mday;
        ap->stAntigas[ap->quantidadeStAntigas - 1].fim.mes = infoTempoLocal->tm_mon + 1;
        ap->stAntigas[ap->quantidadeStAntigas - 1].fim.ano = infoTempoLocal->tm_year + 1900;

        strcpy(ap->nomeStreamAtual, " ");
        strcpy(ap->nomeCategoriaAtual, " ");
}

void iniciaST(Apresentador *p){
    struct tm *infoTempoLocal = tempoAtual();
    p->stAntigas[p->quantidadeStAntigas - 1].inicio.dia = infoTempoLocal->tm_mday;
    p->stAntigas[p->quantidadeStAntigas - 1].inicio.mes = infoTempoLocal->tm_mon + 1;
    p->stAntigas[p->quantidadeStAntigas - 1].inicio.ano = infoTempoLocal->tm_year + 1900;

    p->stAntigas[p->quantidadeStAntigas - 1].fim.dia = 0;
    p->stAntigas[p->quantidadeStAntigas - 1].fim.mes = 0;
    p->stAntigas[p->quantidadeStAntigas - 1].fim.ano = 0;

    free(infoTempoLocal); 
}


Apresentador *criaApresentador(char *nome, char *nomeCat, char *nomeST){
    Apresentador *novo = alocarApresentador(); 
    if(!novo) return NULL;

    char tempNome[50], tempNomeST[50];

    strcpy(tempNome, nome); deixaMaiuscula(tempNome);
    strcpy(novo->nome, tempNome);

    strcpy(tempNome, nomeCat); deixaMaiuscula(tempNome);
    strcpy(novo->nomeCategoriaAtual, tempNome);

    strcpy(tempNomeST, nomeST); deixaMaiuscula(tempNomeST);
    strcpy(novo->nomeStreamAtual, tempNomeST);

    novo->quantidadeStAntigas = 1;
    strcpy(novo->stAntigas[novo->quantidadeStAntigas - 1].nome, tempNomeST);

    iniciaST(novo);

    novo->prox = novo->ant = NULL;

    return novo;
}

int cadastrarCategoria(Categorias *nova, char *nomeST, Arvore *arvST){
    int cadastrou = 0;
    deixaMaiuscula(nomeST);
    Arvore *stream = buscarNaArvore(arvST, nomeST);

    if (stream) {
        Categorias **lista = &(stream->dado.STREAM.categorias);
        if (*lista) {  
            if (existeCategoria(*lista, nova->nome) == 0) {
                cadastrou = 1;
                Categorias *atual = *lista;
                Categorias *anterior = NULL;
                // Procurar posição para inserir em ordem
                do {
                    if (strcmp(nova->nome, atual->nome) < 0) break;
                    anterior = atual;
                    atual = atual->prox;
                } while (atual != *lista);

                if (anterior == NULL) {

                    Categorias *ultimo = *lista;
                    while (ultimo->prox != *lista) ultimo = ultimo->prox;
                    ultimo->prox = nova;
                    nova->prox = *lista;
                    *lista = nova; 
                } else {
                    anterior->prox = nova;
                    nova->prox = atual;
                }
            }
        } else {
            cadastrou = 1;
            *lista = nova;
            nova->prox = nova; 
        }
    }
    return cadastrou;
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

            if(atual){
                if(strcmp(novo->nome, atual->nome) != 0){
                    inseriu = 1;
                    ant->prox = novo;
                    novo->ant = ant;
                    atual->ant = novo;
                    novo->prox = atual;
                }
            }else {
                inseriu = 1;
                ant->prox = novo;
                novo->ant = ant;
            }
        }
    } else {
        (*lista) = novo;
        inseriu = 1;
    }

    return inseriu;
}

int cadastrarApresentador(Apresentador *novo, Arvore *arvST, Apresentador **listaAP){
    int cadastrar = 0;
    if(existeApresentador(*listaAP, novo->nome) == 0){
        Arvore *stream = buscarNaArvore(arvST, novo->nomeStreamAtual);
        if(stream){
            if(stream->dado.STREAM.categorias){
                int existe = existeCategoria(stream->dado.STREAM.categorias, novo->nomeCategoriaAtual);
                if(existe){
                    cadastrar = inserirApresentadorOrdenado(listaAP, novo);
                }
            }
            
        }
    }

    return cadastrar;
}

// FUNÇÕES DE MOSTRAR/REMOVER DE LISTAS E FUNÇÕES

void mostrarCategoriasDeST(char *nome, Arvore *arvST){
    deixaMaiuscula(nome);
    Arvore *stream = buscarNaArvore(arvST, nome);
    if(stream){
        if(stream->dado.STREAM.categorias){
            Categorias *atual = stream->dado.STREAM.categorias;
            do{
                printf("%s\n", atual->nome);
                atual = atual->prox;
            }while(atual != stream->dado.STREAM.categorias);
        }
    }
}

Categorias *buscaCategoria(Categorias *lista, char *nome){
    deixaMaiuscula(nome);
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
    deixaMaiuscula(nomeCateg);
    deixaMaiuscula(nomeST);
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if(stream){
        if(existeCategoria(stream->dado.STREAM.categorias, nomeCateg)){
            Categorias *categoria = buscaCategoria(stream->dado.STREAM.categorias, nomeCateg);
            imprimirArvore(categoria->programa);
        }
    }
}

void mostrarStsQueTemCategoria(char *nomeCateg, Arvore *arvST){
    deixaMaiuscula(nomeCateg);
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

    return removeu;
}

// AUXILIA FUNÇÕES DE ALTERAR

Arvore *existeApresentadorEmPrograma(Arvore *programa, char *nomeAP){
    deixaMaiuscula(nomeAP);
    Arvore *busca = NULL;
    if(programa){
        if(strcmp(programa->dado.PROGRAMA.NomeApresentador, nomeAP) == 0) busca = programa;
        existeApresentadorEmPrograma(programa->esq, nomeAP);
        existeApresentadorEmPrograma(programa->dir, nomeAP);
            
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

int alterarStreamDeApresentador_removePrograma(Arvore *streams, Apresentador *apresentador, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma){
    int i = 0;
    deixaMaiuscula(nomeNovaStream);
    deixaMaiuscula(categoriaNovoPrograma);
  
    Arvore *atualST = buscarNaArvore(streams, apresentador->nomeStreamAtual);
    Arvore *novaST = buscarNaArvore(streams, nomeNovaStream);


    if((atualST && novaST) && strcmp(atualST->dado.STREAM.nome, novaST->dado.STREAM.nome) != 0){
  
        Categorias *CTnova = novaST->dado.STREAM.categorias;
        Arvore *res = NULL;
        Categorias *cat = existeApresentadorEmCategorias(CTnova, apresentador->nome, &res);

        if(!res){


            int j = existeCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);

            if(j){
                Categorias *auxi;
                encerraST(apresentador);
                res = NULL;
                cat = existeApresentadorEmCategorias(atualST->dado.STREAM.categorias, apresentador->nome, &res); 
                removerDaArvore(&(cat->programa), res);

                apresentador->quantidadeStAntigas += 1;
                strcpy(apresentador->stAntigas[apresentador->quantidadeStAntigas - 1].nome, novaST->dado.STREAM.nome);
                iniciaST(apresentador);
                strcpy(apresentador->nomeStreamAtual, novaST->dado.STREAM.nome);
                strcpy(apresentador->nomeCategoriaAtual, categoriaNovoPrograma);
                
                auxi = buscaERetornaCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);
                i = inserirArvBin(&(auxi->programa), novoPrograma);
            }
        }
    }

    return i;
}

// ALTERAR COLOCANDO OUTRO APRESENTADR NO PROGRAMA ANTIGO DO APRESENTADOR

int alterarStreamDeApresentador_substituiApresentadorPrograma(Arvore *streams, Apresentador **lista, Apresentador *apresentador, Apresentador *substituto, char *nomeNovaStream, Arvore *novoPrograma, char *categoriaNovoPrograma){
    int i = 0;
    deixaMaiuscula(nomeNovaStream);
    deixaMaiuscula(categoriaNovoPrograma);
    Arvore *atualST = buscarNaArvore(streams, apresentador->nomeStreamAtual);
    Arvore *novaST = buscarNaArvore(streams, nomeNovaStream);

    if((atualST && novaST) && strcmp(atualST->dado.STREAM.nome, novaST->dado.STREAM.nome) != 0){
        
        Categorias *CTnova = novaST->dado.STREAM.categorias;
        Arvore *res = NULL;
        Categorias *cat = existeApresentadorEmCategorias(CTnova, apresentador->nome, &res);

        if(!res){

            int j = existeCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);

            if(j){
                Categorias *auxi;
 
                int k = cadastrarApresentador(substituto, atualST, lista);
                if(k){

                    encerraST(apresentador);
                    res = NULL;
                    cat = existeApresentadorEmCategorias(atualST->dado.STREAM.categorias, apresentador->nome, &res); 

                    strcpy(res->dado.PROGRAMA.NomeApresentador, substituto->nome);
                    iniciaST(substituto);
                    strcpy(substituto->nomeStreamAtual, atualST->dado.STREAM.nome);

                    apresentador->quantidadeStAntigas += 1;
                    strcpy(apresentador->stAntigas[apresentador->quantidadeStAntigas - 1].nome, novaST->dado.STREAM.nome);
                    iniciaST(apresentador);
                    strcpy(apresentador->nomeStreamAtual, novaST->dado.STREAM.nome);
                    strcpy(apresentador->nomeCategoriaAtual, categoriaNovoPrograma);
                    
                    auxi = buscaERetornaCategoria(novaST->dado.STREAM.categorias, categoriaNovoPrograma);
                    i = inserirArvBin(&(auxi->programa), novoPrograma);
                }
                
            }
        }
    }

    return i;
}


// PEDRO

int compararDiaSemana(DiaSemana d1, DiaSemana d2) {
    int resultado = 0; // iguais
    if (d1 < d2) resultado = -1;
    else if (d1 > d2) resultado = 1;
    return resultado;
}

void mostrarProgramasPorDiaSemana(Arvore *raiz, DiaSemana dia) {
    if(raiz) {
        mostrarProgramasPorDiaSemana(raiz->esq, dia);

        if(raiz->tipo == PROGRAMA) {
            if(raiz->dado.PROGRAMA.data.diasemana == dia) {
                printf("[PROGRAMA] Nome: %s | Apresentador: %s | Dia: %d | Inicio: %s | Tempo: %d\n",
                    raiz->dado.PROGRAMA.nome,
                    raiz->dado.PROGRAMA.NomeApresentador,
                    raiz->dado.PROGRAMA.data.diasemana,
                    raiz->dado.PROGRAMA.HorarioInicio,
                    raiz->dado.PROGRAMA.Tempo);
            }
        }

        mostrarProgramasPorDiaSemana(raiz->dir, dia);
    }
}

void imprimiPGDiaHorario(Arvore *raiz, DiaSemana dia, char *horario){
    if(raiz){
        if(raiz->dado.PROGRAMA.data.diasemana == dia && strcmp(raiz->dado.PROGRAMA.HorarioInicio, horario) == 0){
            printf("[PROGRAMA] Nome: %s | Apresentador: %s | Dia: %d | Inicio: %s | Tempo: %d\n",
                    raiz->dado.PROGRAMA.nome,
                    raiz->dado.PROGRAMA.NomeApresentador,
                    raiz->dado.PROGRAMA.data.diasemana,
                    raiz->dado.PROGRAMA.HorarioInicio,
                    raiz->dado.PROGRAMA.Tempo);
        }
        imprimiPGDiaHorario(raiz->esq, dia, horario);
        imprimiPGDiaHorario(raiz->dir, dia, horario);
    }
}

void mostrarProgramasDeStreamPorDiaSemanaHorario(Arvore *arvST, char *nomeST, char *horario, DiaSemana dia) {
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if(stream) {
        Categorias *cat = stream->dado.STREAM.categorias;
        if(cat) {
            Categorias *atual = cat;
            do{
                if(atual->programa){
                    imprimiPGDiaHorario(atual->programa, dia, horario);
                }
                atual = atual->prox;
            }while(atual != cat);
        }else printf("Essa stream não tem categorias nem programas!\n");
    }else printf("Stream %s não encontrada.\n", nomeST);
}

void imprimeStreamsPorCategoria(Arvore *arvST, TipoCategoria tipo) {
    if(arvST) {
        imprimeStreamsPorCategoria(arvST->esq, tipo);

        Categorias *lista = arvST->dado.STREAM.categorias;
        if(lista) {
            Categorias *atual = lista;
            int achou = 0;

            do {
                if(atual->tipo == tipo) {
                    achou = 1;
                }
                atual = atual->prox;
            } while(atual != lista && !achou);

            if(achou) {
                printf("[STREAM] Nome: %s | Site: %s\n",
                    arvST->dado.STREAM.nome,
                    arvST->dado.STREAM.Site);
            }
        }

        imprimeStreamsPorCategoria(arvST->dir, tipo);
    }
}

void mostrarProgramasDeCategoriaPorDiaSemana(Arvore *arvST, char *nomeST, char *nomeCateg, DiaSemana dia) {
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if(stream) {
        Categorias *categoria = buscaCategoria(stream->dado.STREAM.categorias, nomeCateg);
        if(categoria) {
            mostrarProgramasPorDiaSemana(categoria->programa, dia);
        } else {
            printf("Categoria %s não encontrada na stream %s.\n", nomeCateg, nomeST);
        }
    } else {
        printf("Stream %s não encontrada.\n", nomeST);
    }
}

void mostrarApresentadoresDeStream(Apresentador *lista, char *nomeST) {
    if(!lista) {
        printf("Nenhum apresentador cadastrado.\n");
        return;
    }

    deixaMaiuscula(nomeST);  

    Apresentador *atual = lista;
    int encontrou = 0;

    while(atual) {
        if(strcmp(atual->nomeStreamAtual, nomeST) == 0) {
            printf("[APRESENTADOR] Nome: %s | Categoria: %s | Stream Atual: %s\n",
                   atual->nome,
                   atual->nomeCategoriaAtual,
                   atual->nomeStreamAtual);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if(!encontrou) {
        printf("Nenhum apresentador encontrado na stream %s.\n", nomeST);
    }
}

void mostrarDadosdeumProgramadeumaCategoriadeumaStream(Arvore *arvST, char *nomeST, char *nomeCateg, char *nomeProg){
    deixaMaiuscula(nomeCateg);
    deixaMaiuscula(nomeProg);
    deixaMaiuscula(nomeST);
    Arvore *stream = buscarNaArvore(arvST, nomeST);
    if (stream){
        Categorias *categoria = buscaCategoria(stream->dado.STREAM.categorias, nomeCateg);
        if (categoria){
            Arvore *prog = buscarNaArvore(categoria->programa, nomeProg);
            if(prog){
                printf("[PROGRAMA] Nome: %s | Apresentador: %s | Inicio: %s | Tempo: %d\n",
                       prog->dado.PROGRAMA.nome,
                       prog->dado.PROGRAMA.NomeApresentador,
                       prog->dado.PROGRAMA.HorarioInicio,
                       prog->dado.PROGRAMA.Tempo);
            }
            else printf("Programa %s não encontrado na categoria %s da stream %s.\n", nomeProg, nomeCateg, nomeST);
        } else printf("Categoria %s não encontrada na stream %s.\n", nomeCateg, nomeST);         
    } else printf("Stream %s não encontrada.\n", nomeST); 
}

void mostrarApresentadoresDeCategoria(Apresentador *lista, char *nomeCategoria) {
    if (lista){
        deixaMaiuscula(nomeCategoria);  // padroniza entrada

        Apresentador *atual = lista;
        int encontrou = 0;

        while(atual) {
            if(strcmp(atual->nomeCategoriaAtual, nomeCategoria) == 0) {
                printf("[APRESENTADOR] Nome: %s | Categoria: %s | Stream Atual: %s\n",
                    atual->nome,
                    atual->nomeCategoriaAtual,
                    atual->nomeStreamAtual);
                encontrou = 1;
            }
            atual = atual->prox;
        }

        if(!encontrou) printf("Nenhum apresentador encontrado na categoria %s.\n", nomeCategoria);
    }

    
}
