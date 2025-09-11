#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#include "prototipos.h"

void menu(){
    printf("--- MENU ---\n");
    printf("1 - Cadastrar stream\n");
    printf("2 - Cadastrar categoria\n");
    printf("3 - Cadastrar apresentadores de Stream\n");
    printf("4 - Cadastrar programa\n");

    printf("\n");

    printf("5 - Mostrar todas as streams cadastradas\n");
    printf("6 - Mostrar todas as streams que tem uma categoria\n");
    printf("7 - Mostrar todas as streams que tem um determinado tipo de categoria\n");
    printf("8 - Mostrar todas as categorias de uma stream\n");

    printf("\n");

    printf("9 - Mostrar todos os programas de uma categoria de uma stream\n");
    printf("10 - Mostrar programas de stream por dia e horário\n");
    printf("11 - Mostrar todos os programas de um determinado dia de uma categoria de uma stream\n");
    printf("12 - Mostrar dados de um programa de uma categoria de uma stream\n");

    printf("\n");

    printf("13 - Mostrar todos os apresentadores de uma stream\n");
    printf("14 - Mostrar apresentadores de uma categoria independente da stream que ele trabalha\n");

    printf("\n");

    printf("15 - Remover programa de uma categoria de uma stream\n");;
    printf("16 - Remover categoria de uma stream\n");
    printf("17 - Alterar stream que um apresentador\n");

    printf("0 - Sair\n");

    printf("\n");
}

void menuAltAP(){
    printf("-- MENU ALTERAR --\n");
    printf("1 - Remover programa\n");
    printf("2 - Alterar apresentador\n");
}

void menuTipoCatgoria(){
    printf("-- MENU TIPO CATEGORIA --\n");
    printf("1 - NOTICIA\n");
    printf("2 - ENTRETENIMENTO\n");
    printf("3 - ESPORTE\n");
}

void menuDiaSemana(){
    printf("-- MENU DIA DA SEMANA --\n");
    printf("1 - DOMINGO\n");
    printf("2 - SEGUNDA\n");
    printf("3 - TERÇA\n");
    printf("4 - QUARTA\n");
    printf("5 - QUINTA\n");
    printf("6 - SEXTA\n");
    printf("7 - SÁBADO\n");

}


int main(){
    setlocale(LC_ALL, "Portuguese");

    int parada = 1;

    Arvore *streams = inicializar();
    Apresentador *apresentadores = NULL;

    int op, opTipoCT, verifica, opDia;
    char nomeCat[50], nomeST[50], nomeAP[50], nomePG[50];

    while(parada){
        printf("\n");
        menu();

        printf("\nOpção: "); scanf("%d", &op);
        printf("\n");
        switch (op){
            case 1:
                printf("CADASTRANDO STREAM\n\n");

                Arvore *nova = alocar(STREAM);
                if(!nova) exit(1);
                preencherDado(STREAM, nova);
                printf("\n");

                if((verifica = inserirArvBin(&streams, nova))) 
                    printf("Stream inserida na árvore com sucesso.\n");
                else printf("Essa stream já existe na árvore, logo não foi possível inserir.\n");
                
                break;
            case 2:
                printf("CADASTRAND0 CATEGORIA\n\n");

                menuTipoCatgoria();
                printf("\nOpção: "); scanf("%d", &opTipoCT); printf("\n");
                if(opTipoCT > 0 && opTipoCT < 4){

                    Categorias *nova = alocarCategoria(nova);
                    if(!nova) exit(1);
                    TipoCategoria tipo = opTipoCT;

                    printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                    nova = criaCategoria(tipo, nomeCat);
                    printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                    verifica = cadastrarCategoria(nova, nomeST, streams);

                    if(verifica) printf("\nCategoria cadastrada com sucesso!");
                    else printf("\nNão foi possível cadastrar categoria, tente novamente e verifique suas informações.");

                }else printf("\nOpção de categoria inválida.");
                break;
            case 3:
                printf("CADASTRANDO APRESENTADORES DA STREAM\n\n");

                int R;
                printf("Digite o nome da Stream que deseja cadastrar os apresentadores: "); scanf(" %[^\n]", nomeST);
                
                do{
                    printf("Nome do apresentador: "); scanf(" %[^\n]", nomeAP);
                    printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);

                    Apresentador *novoAP = alocarApresentador();
                    if(!novoAP) exit(1); 
                    novoAP = criaApresentador(nomeAP, nomeCat, nomeST);
                    if(novoAP){
                        verifica = cadastrarApresentador(novoAP, streams, &apresentadores);
                        if(verifica) printf("\nApresentador adicionado a lista com sucesso!");
                        else printf("\nNão foi possível adicionar esse apresentador a lista!");
                    }else printf("\nErro ao criar apresentador!");
                    printf("Você deseja cadastrar outro apresentador na stream %s? ( 0 - não | 1 - sim)", nomeST);
                    scanf("%d", &R);
                }while(R == 1);
                break;
            case 4:
            printf("CADASTRANDO PROGRAMA\n\n");

                printf("Stream do programa: "); scanf(" %[^\n]", nomeST);
                Arvore *stream = buscarNaArvore(streams, nomeST);

                if(stream){
                    if(stream->dado.STREAM.categorias){
                        printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);

                        int existe = existeCategoria(stream->dado.STREAM.categorias, nomeCat);

                        if(existe){
                            Arvore *novo = alocar(PROGRAMA);
                            if(!novo) exit(1);
                            preencherDado(PROGRAMA, novo);

                            verifica = validarApresentador(apresentadores, novo->dado.PROGRAMA.NomeApresentador, nomeST, nomeCat);

                            Arvore *res = NULL;
                            existeApresentadorEmCategorias(stream->dado.STREAM.categorias, novo->dado.PROGRAMA.NomeApresentador, &res);

                            if(verifica && res == NULL){
                                int i = inserirArvBin(&(stream->dado.STREAM.categorias->programa), novo);
                                
                                if(!i){
                                    printf("\nNão foi possível inserir esse programa pois o mesmo já existe na stream!");
                                    free(novo);
                                }
                                else printf("\nPrograma inserido com sucesso!");
                            }else {
                                printf("\nApresentador inválido!");
                                free(novo);
                            }
                        } else printf("\nEssa categoria não existe na stream!");
                    }else printf("\nEssa stream não possui categorias para o programa!");
                }else printf("\nStream não encontrada!");
                break;   
            case 5:
                printf("--TODAS AS STREAMS CADASTRADAS--\n\n");

                imprimirArvore(streams);
                break;
            case 6:
                printf("--TODAS AS STREAMS CADASTRADAS NA CATEGORIA %S--\n\n");

                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                mostrarStsQueTemCategoria(nomeCat, streams);
                break;
            case 7:
                printf("--TODAS AS STREAMS DO TIPO DE CATEGORIA--\n\n ");

                menuTipoCatgoria();
                int opCat;
                printf("Opção: "); scanf("%d", &opCat);
                if(opCat > 0 && opCat < 4){
                    TipoCategoria tipo = opCat;
                    imprimeStreamsPorCategoria(streams, tipo);
                }else printf("\nOpção de categoria inválida!");
                break;
            case 8:
                printf("--TODAS AS CATEGORIAS DE UMA STREAM--\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                mostrarCategoriasDeST(nomeST, streams);
                break;
            case 9:
                printf("--TODOS OS PROGRAMAS DE UMA CATEGORIA DE UMA STREAM--\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                mostrarProgsDeCategDeST(nomeST, streams, nomeCat);
                break;
            case 10:
                printf("--TODOS OS PROGRAMAS DE UMS STREAM POR DIA E HORARIO--\n\n");

                menuDiaSemana();
                printf("\nOpção: "); scanf("%d", &opDia);
                if(opDia > 0 && opDia < 8){
                    printf("\nNome da stream: "); scanf(" %[^\n]", nomeST);
                    DiaSemana dia = opDia;
                    char horario[10]; 
                    printf("Horário: "); scanf(" %[^\n]", horario);

                    mostrarProgramasDeStreamPorDiaSemanaHorario(streams, nomeST, horario, dia);
                }else printf("\nOpção de dia inválida!");
                break;
            case 11:
                printf("--TODOS OS PROGRAMAS DE UM DETERMINADO DIA DE UMA CATEGORIA DE UMA STREAM--\n\n");

                menuDiaSemana();
                printf("\nOpção: "); scanf("%d", &opDia);
                if(opDia > 0 && opDia < 8){
                    printf("\nNome da stream: "); scanf(" %[^\n]", nomeST);
                    printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                    DiaSemana dia = opDia;
                    
                    mostrarProgramasDeCategoriaPorDiaSemana(streams, nomeST, nomeCat, dia);
                }else printf("Opção de dia inválida!\n");
                break;
            case 12:
                printf("--DADOS DE UM PROGRAMA DE UMA CATEGORIA DE UMA STREAM--\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                printf("Nome do programa: "); scanf(" %[^\n]", nomePG);

                mostrarDadosdeumProgramadeumaCategoriadeumaStream(streams, nomeST, nomeCat, nomePG);
                break;
            case 13:
                printf("--TODOS OS APRESENTADORES DE UMA STREAM--\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                mostrarApresentadoresDeStream(apresentadores, nomeST);
                break;
            case 14:
                printf("--TODOS OS APRESENTADORES DE UMA CATEGORIA INDEPENDENTE DA STREAM QUE ELE TRABALHA--\n\n");

                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                mostrarApresentadoresDeCategoria(apresentadores, nomeCat);
                break;
            case 15:
                printf("REMOVENDO UM PROGRAMA DE UMA CATEGORIA DE UMA STREAM\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);
                printf("Nome do programa: "); scanf(" %[^\n]", nomePG);

                verifica = removerProgramaDeCateDeST(streams, nomeST, nomeCat, nomePG);
                if(verifica) printf("\nRemovido com sucesso!");
                else printf("\nNão foi possível remover!");
                break;
            case 16:
                printf("REMOVENDO UMA  CATEGORIA DE UMA STREAM\n\n");

                printf("Nome da stream: "); scanf(" %[^\n]", nomeST);
                printf("Nome da categoria: "); scanf(" %[^\n]", nomeCat);

                verifica = removerCategDeST(streams, nomeST, nomeCat);
                if(verifica) printf("\nRemovida com sucesso!");
                else printf("\nNão foi possível remover!");
                break;
            case 17:
                printf("ALTERANDO A STREAM DE UM APRESENTNADOR\n\n");

                menuAltAP();
                int opAlt;
                printf("\nOpção: "); scanf("%d", &opAlt);

                if(opAlt > 0 && opAlt < 3){
                    printf("\nNome do apresentador: "); scanf(" %[^\n]", nomeAP);
                    Apresentador *ap = buscaApresentador(apresentadores, nomeAP);

                    if(ap){
                        printf("Nome da nova stream: "); scanf(" %[^\n]", nomeST);
                        printf("Nome da nova categoria: "); scanf(" %[^\n]", nomeCat);
                        Arvore *novoPG = alocar(PROGRAMA);
                        if(!novoPG){
                            printf("\nErro ao criar novo programa!\n");
                            exit(1);
                        }
                        printf("-- NOVO PROGRAMA --\n");
                        preencherDado(PROGRAMA, novoPG);
                        if(opAlt == 1){
                            verifica = alterarStreamDeApresentador_removePrograma(streams, ap, nomeST, novoPG, nomeCat);

                            if(verifica) printf("\nApresentador alterado com sucesso!\n");
                            else printf("\nNão foi possível alterar apresentador, verifique suas informações!\n");
                        }else if(opAlt == 2){
                            char sub[50];
                            printf("Nome do apresentador substituto: "); scanf(" %[^\n]", sub);
                            Apresentador *substituto = criaApresentador(sub, ap->nomeCategoriaAtual, ap->nomeStreamAtual);
                            if(substituto){
                                verifica = alterarStreamDeApresentador_substituiApresentadorPrograma(streams, &apresentadores, ap, substituto, nomeST, novoPG, nomeCat);

                                if(verifica) printf("\nApresentador alterado com sucesso!\n");
                                else printf("\nNão foi possível alterar apresentador, verifique suas informações!\n");
                            }else printf("\nErro ao alocar memória do substituto!\n");
                        }else printf("\nOpção inválida!"); 
                    }else printf("\nApresentador não existe!");
                } else printf("\nOpção inválida!\n");
                break;
            case 0:
                parada = 0;
                break;

            default:
                printf("\nEscolha uma opção válida!");
                break;
        }
    }

 

    return 0;
}
