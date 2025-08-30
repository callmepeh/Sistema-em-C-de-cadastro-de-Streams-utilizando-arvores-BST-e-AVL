#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#include "prototipos.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    Arvore *streams = NULL;

    Arvore *novaStream = (Arvore *)malloc(sizeof(Arvore));
    if(!novaStream){
        printf("Ocorreu um erro ao alocar memoria.\n");
        exit(1);
    }

    criarNo(STREAM, &novaStream);
    int verifica = inserirArvBin(&streams, novaStream);
    if(verifica) printf("Stream inserida na arvore com sucesso.\n");
    else printf("Essa stream ja existe na arvore, logo nao foi possivel inserir.\n");

    printf(" \n");

    // inserir outra

    Arvore *outraSTream = (Arvore *)malloc(sizeof(Arvore));
    if(!outraSTream){
        printf("Ocorreu um erro ao alocar memoria.\n");
        exit(1);
    }

    criarNo(STREAM, &outraSTream);
    verifica = inserirArvBin(&streams, outraSTream);
    if(verifica) printf("Stream inserida na arvore com sucesso.\n");
    else printf("Essa stream ja existe na arvore, logo nao foi possivel inserir.\n");

    printf(" \n");

    imprimirArvore(streams);

    printf(" \n");

    //programas

    Arvore *programas = NULL;
    Arvore *novaPrograma = (Arvore *)malloc(sizeof(Arvore));
    if(!novaPrograma){
        printf("Ocorreu um erro ao alocar memoria.\n");
        exit(1);
    }

    criarNo(PROGRAMA, &novaPrograma);
    verifica = inserirArvBin(&programas, novaPrograma);
    if(verifica) printf("Programa inserido na arvore com sucesso.\n");
    else printf("Esse programa ja existe na arvore, logo nao foi possivel inserir.\n");

    printf(" \n");

    // inserir outra

    Arvore *outroPrgrama = (Arvore *)malloc(sizeof(Arvore));
    if(!outroPrgrama){
        printf("Ocorreu um erro ao alocar memoria.\n");
        exit(1);
    }

    criarNo(PROGRAMA, &outroPrgrama);
    verifica = inserirArvBin(&programas, outroPrgrama);
    if(verifica) printf("Stream inserida na arvore com sucesso.\n");
    else printf("Essa stream ja existe na arvore, logo nao foi possivel inserir.\n");

    printf(" \n");

    imprimirArvore(programas);

    printf(" \n");

    Arvore *busca = buscarNaArvore(programas, "dexter");
    if(busca) printf("Programa encontrado.\n");
    else printf("Programa não encontrado.\n");

    return 0;
}