#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#include "prototipos.h"

void menu(){
    printf("--- MENU ---\n");
    printf("1 - Cadastrar stream\n");
    printf("2 - Cadastrar categoria\n");
    printf("3 - Cadastrar programa\n");
    printf("4 - Cadastrar apresentador\n");

    printf("\n");

    printf("5 - Mostrar todas as streams cadastradas\n");
    printf("6 - Mostrar todas as streams que tem uma categoria\n");
    printf("7 - Mostrar todas as streams que tem uma categoria\n");
    printf("8 - Mostrar todas as streams que tem um determinado tipo de categoria\n");
    printf("9 - Mostrar todas as categorias de uma stream\n");

    printf("\n");

    printf("10 - Mostrar todos os programas de uma categoria de uma stream\n");
    printf("11 - Mostrar programas de stream por dia e horário\n");
    printf("12 - Mostrar todos os programas de um determinado dia de uma categoria de uma stream\n");
    printf("13 - Mostrar dados de um programa de uma categoria de uma stream\n");

    printf("\n");

    printf("14 - Mostrar todos os apresentadores de uma stream\n");
    printf("15 - Mostrar apresentadores de uma categoria independente da stream que ele trabalha\n");

    printf("\n");

    printf("16 - Remover programa de uma categoria de uma stream\n");;
    printf("17 - Remover categoria de uma stream\n");
    printf("18 - Alterar stream que um apresentador\n");

    printf("\n");
}

void menuAltAP(){
    printf("-- MENU ALTERAR --");
    printf("1 - Remover programa\n");
    printf("2 - Alterar apresentador\n");
}

void menuTipoCatgoria(){
    printf("-- MENU TIPO CATEGORIA --");
    printf("1 - NOTICIA\n");
    printf("2 - ENTRETENIMENTO\n");
    printf("3 - ESPORTE\n");
}

TipoCategoria retornaTipo(int i){
    TipoCategoria tipo;
    if(i == 1) tipo = NOTICIA;
    else if(i == 2) tipo = ENTRETENIMENTO;
    else tipo = ESPORTE;
    return tipo;
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    Arvore *streams = inicializar();
    int op, opTipoCT, verifica;
    char nomeCat[50], nomeST[50];

    menu();

    printf("\nOpção: "); scanf("%d", &op);
    switch (op){
        case 1:
            Arvore *nova;
            if(!(nova = alocar(nova, STREAM))) exit(1);
            preencherDado(STREAM, &nova);

            if((verifica = inserirArvBin(&streams, nova))) 
                printf("Stream inserida na árvore com sucesso.\n");
            else printf("Essa stream já existe na árvore, logo não foi possível inserir.\n");
            
            break;
        case 2:
            menuTipoCatgoria();
            printf("\nOpção: "); scanf("%d", &opTipoCT);
            if(op > 0 && op < 4){

                Categorias *nova;
                if(!(nova = alocarCategoria(nova))) exit(1);
                TipoCategoria tipo = retornaTipo(op);

                printf("\nNome da categoria: "); scanf(" %[^\n]", nomeCat);
                nova = criaCategoria(tipo, nomeCat);
                printf("\nNome da stream: "); scanf(" %[^\n]", nomeST);
                verifica = cadastrarCategoria(nova, nomeST, streams);

                if(verifica) printf("\nCategoria cadastrada com sucesso!\n");
                else rintf("\nNão foi possível cadastrar categoria, tente novamente e verifique suas informações.\n");

            }else printf("Opção de categoria inválida.\n");
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;

        default:
            printf("Escolha uma opção válida!\n");
            break;
    }

    return 0;
}