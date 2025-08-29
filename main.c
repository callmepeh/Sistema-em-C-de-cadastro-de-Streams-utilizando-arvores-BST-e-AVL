#include <stdio.h>
#include <stdlib.h>

#include "prototipos.h"

int main(){
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

    imprimirArvore(streams);

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

    imprimirArvore(programas);

    return 0;
}