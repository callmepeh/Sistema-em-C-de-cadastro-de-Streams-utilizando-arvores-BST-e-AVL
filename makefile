CC = gcc
CFLAGS = -Wall -O2

TESTES = teste_insercao.c teste_busca_programas.c

# Compilar versão com ABB (BST)
abb: $(TESTES) BST/funcoes.c
	$(CC) $(CFLAGS) -o teste_insercao_abb teste_insercao.c BST/funcoes.c
	$(CC) $(CFLAGS) -o teste_busca_abb teste_busca_programas.c BST/funcoes.c

# Compilar versão com AVL
avl: $(TESTES) AVL/funcoes.c
	$(CC) $(CFLAGS) -o teste_insercao_avl teste_insercao.c AVL/funcoes.c
	$(CC) $(CFLAGS) -o teste_busca_avl teste_busca_programas.c AVL/funcoes.c

clean:
	rm -f teste_insercao_abb teste_busca_abb teste_insercao_avl teste_busca_avl
