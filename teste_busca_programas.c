#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AVL/prototipos.h"
#include "BST/prototipos.h"

#define REPETICOES 30

// Função silenciosa: percorre a árvore sem imprimir nada
void percorrerArvoreSilencioso(Arvore *raiz) {
    if (raiz) {
        percorrerArvoreSilencioso(raiz->esq);
        // nada de printf aqui!
        percorrerArvoreSilencioso(raiz->dir);
    }
}

int main() {
    Arvore *raiz = inicializar();

    // Criando uma stream para o teste
    Arvore *st = alocar(STREAM);
    strcpy(st->dado.STREAM.nome, "STREAM_TESTE");
    strcpy(st->dado.STREAM.Site, "site.com");
    st->dado.STREAM.categorias = NULL;
    inserirArvBin(&raiz, st);

    // Criando categoria
    Categorias *cat = criaCategoria(1, "CATEGORIA_TESTE");
    cadastrarCategoria(cat, "STREAM_TESTE", raiz);

    // Inserindo alguns programas na categoria
    for (int i = 0; i < 1000; i++) {
        Arvore *prog = alocar(PROGRAMA);
        sprintf(prog->dado.PROGRAMA.nome, "PROG_%d", i);
        strcpy(prog->dado.PROGRAMA.NomeApresentador, "APRESENTADOR_TESTE");
        strcpy(prog->dado.PROGRAMA.HorarioInicio, "10:00");
        prog->dado.PROGRAMA.Tempo = 60;
        inserirArvBin(&(cat->programa), prog);
    }

    // Medindo tempo de busca
    double soma_tempos = 0;
    for (int i = 0; i < REPETICOES; i++) {
        clock_t inicio = clock();

        // Busca (sem printf dentro)
        Arvore *stream = buscarNaArvore(raiz, "STREAM_TESTE");
        if (stream) {
            Categorias *categoria = buscaCategoria(stream->dado.STREAM.categorias, "CATEGORIA_TESTE");
            if (categoria) {
                percorrerArvoreSilencioso(categoria->programa);
            }
        }

        clock_t fim = clock();
        soma_tempos += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    double tempo_medio = soma_tempos / REPETICOES;
    printf("Tempo medio de busca de programas (repetido %d vezes): %f segundos\n",
           REPETICOES, tempo_medio);

    return 0;
}
