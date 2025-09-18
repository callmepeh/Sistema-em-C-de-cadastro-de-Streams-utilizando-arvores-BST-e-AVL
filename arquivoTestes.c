#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BST/prototipos.h"
#include "AVL/prototipos.h"

#define N 10000
#define REPETICOES 30

typedef enum { BST, AVL } TipoArvore;
typedef enum { ORDENADA, ALEATORIA } TipoInsercao;

// Função para embaralhar um vetor de inteiros
void embaralha(int *vet, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        int tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

int main() {
    srand(time(NULL));
    for (int tipo = BST; tipo <= AVL; tipo++) {
        for (int ordem = ORDENADA; ordem <= ALEATORIA; ordem++) {
            Arvore *raiz = inicializar();
            clock_t inicio, fim;
            double tempo_insercao = 0, tempo_busca = 0;
            char *tipo_nome = tipo == BST ? "BST" : "AVL";
            char *ordem_nome = ordem == ORDENADA ? "ORDENADA" : "ALEATORIA";

            // Prepara vetor de índices
            int *indices = malloc(N * sizeof(int));
            for (int i = 0; i < N; i++) indices[i] = i;
            if (ordem == ALEATORIA) embaralha(indices, N);

            // -------- INSERÇÃO --------
            inicio = clock();
            for (int k = 0; k < N; k++) {
                int i = indices[k];
                Arvore *novo = alocar(STREAM);
                sprintf(novo->dado.STREAM.nome, "STREAM_%d", i);
                sprintf(novo->dado.STREAM.Site, "SITE_%d.com", i);
                novo->dado.STREAM.categorias = NULL;
                inserirArvBin(&raiz, novo); // Chama sempre a mesma função
            }
            fim = clock();
            tempo_insercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            // -------- BUSCA --------
            for (int r = 0; r < REPETICOES; r++) {
                inicio = clock();
                for (int k = 0; k < N; k++) {
                    int i = indices[k]; // busca na mesma ordem de inserção
                    char nome[32];
                    sprintf(nome, "STREAM_%d", i);
                    buscarNaArvore(raiz, nome); // Chama sempre a mesma função
                }
                fim = clock();
                tempo_busca += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            }
            tempo_busca /= REPETICOES;

            printf("[%s][%s] Inserção de %d streams: %f segundos\n", tipo_nome, ordem_nome, N, tempo_insercao);
            printf("[%s][%s] Busca média de %d streams (repetido %d vezes): %f segundos\n", tipo_nome, ordem_nome, N, REPETICOES, tempo_busca);

            // Salvar para gráfico
            FILE *f = fopen("tempos.csv", "a");
            fprintf(f, "%s,%s,%d,%f,%f\n", tipo_nome, ordem_nome, N, tempo_insercao, tempo_busca);
            fclose(f);

            free(indices);
        }
    }
    return 0;
}