#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/prototipos.h"
#include "BST/prototipos.h"

#define N 5000000  // ajuste conforme sua máquina

int main() {
    Arvore *raiz = inicializar();
    clock_t inicio, fim;
    double tempo_insercao;

    inicio = clock(); // tempo inicial

    for (int i = 0; i < N; i++) {
        Arvore *novo = alocar(STREAM);
        sprintf(novo->dado.STREAM.nome, "STREAM_%d", i);
        sprintf(novo->dado.STREAM.Site, "SITE_%d.com", i);
        novo->dado.STREAM.categorias = NULL;
        inserirArvBin(&raiz, novo);
    }

    fim = clock(); // tempo final
    tempo_insercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo total de insercao de %d streams: %f segundos\n", N, tempo_insercao);
    return 0;
}
