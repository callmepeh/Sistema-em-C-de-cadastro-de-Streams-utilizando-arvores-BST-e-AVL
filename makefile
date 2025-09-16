CC = gcc
CFLAGS = -Wall -Wextra -g

# ========================
# Alvos principais
# ========================
all: avl bst

# ========================
# Projeto AVL
# ========================
avl: AVL/main.o AVL/funcoes.o
	$(CC) $(CFLAGS) -o avl AVL/main.o AVL/funcoes.o

AVL/main.o: AVL/main.c AVL/prototipos.h
	$(CC) $(CFLAGS) -c AVL/main.c -o AVL/main.o

AVL/funcoes.o: AVL/funcoes.c AVL/prototipos.h
	$(CC) $(CFLAGS) -c AVL/funcoes.c -o AVL/funcoes.o

# ========================
# Projeto BST
# ========================
bst: BST/main.o BST/funcoes.o
	$(CC) $(CFLAGS) -o bst BST/main.o BST/funcoes.o

BST/main.o: BST/main.c BST/prototipos.h
	$(CC) $(CFLAGS) -c BST/main.c -o BST/main.o

BST/funcoes.o: BST/funcoes.c BST/prototipos.h
	$(CC) $(CFLAGS) -c BST/funcoes.c -o BST/funcoes.o

# ========================
# Limpeza
# ========================
clean:
	rm -f AVL/*.o BST/*.o avl bst
