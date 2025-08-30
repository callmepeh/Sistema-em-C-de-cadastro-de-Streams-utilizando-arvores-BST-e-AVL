#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#include "prototipos.h"

// MAIN PARA TESTES

int main(){
    setlocale(LC_ALL, "Portuguese");
    int verifica;
    // INICIALIZA ÁRVORE DE STREAMS
    Arvore *streams = inicializar();

    // ALOCA NOVO NÓ PARA A ÁRVORE DE STREAMS
    Arvore *novaStream;
    if(!(novaStream = alocar(novaStream, STREAM))) exit(1);

    // PREENCHE O NOVO NÓ PARA A ÁRVORE DE STREAMS
    preencherDado(STREAM, &novaStream);

    // INSERE O NOVO NÓ NA ÁRVORE DE STREAMS
    if((verifica = inserirArvBin(&streams, novaStream))) printf("Stream inserida na árvore com sucesso.\n");
    else printf("Essa stream já existe na árvore, logo não foi possível inserir.\n");
    printf(" \n");

    // IMPRIME EM ORDEM ALFABETICA A ÁRVORE DE STREAMS
    imprimirArvore(streams);
    printf(" \n");

    // INICIALIZA A ÁRVORE DE PROGRAMAS 
    Arvore *programas = inicializar();

    // ALOCA UM NOVO NÓ PARA A ÁRVORE DE PROGRAMAS
    Arvore *novaPrograma;;
    if(!(novaPrograma = alocar(programas, PROGRAMA))) exit(1);

    // PREENCHE O NOVO NÓ PARA A ÁRVORE DE PROGRAMAS
    preencherDado(PROGRAMA, &novaPrograma);

    // INSERE NOVO NÓ NA ÁRVORE DE PROGRAMAS
    if((verifica = inserirArvBin(&programas, novaPrograma))) printf("Programa inserido na árvore com sucesso.\n");
    else printf("Esse programa ja existe na arvore, logo não foi possível inserir.\n");
    printf(" \n");

    // IMPRIME EM ORDEM A ÁRVORE DE PROGRAMAS
    imprimirArvore(programas);
    printf(" \n");

    // BUSCA PROGRAMA NA ÁRVORE DE PROGRAMAS
    Arvore *busca;
    if((busca = buscarNaArvore(programas, "dexter"))) printf("Programa encontrado.\n");
    else printf("Programa não encontrado.\n");

    // BUSCA STREAM NA ÁRVORE DE STREAMS
    if((busca = buscarNaArvore(streams, "prime video"))) printf("Stream encontrada.\n");
    else printf("Stream não encontrada.\n");

    return 0;
}