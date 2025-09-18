import matplotlib.pyplot as plt
import csv
import numpy as np

# Estrutura de dados
dados = {
    "ORDENADA": {"BST": [], "AVL": []},
    "ALEATORIA": {"BST": [], "AVL": []}
}

# Leitura do CSV
with open('tempos.csv') as f:
    reader = csv.reader(f)
    for row in reader:
        tipo, ordem, n, ins, bus = row
        n = int(n)
        ins = float(ins)
        bus = float(bus)
        dados[ordem][tipo].append((n, ins, bus))

# --- Gráficos de Inserção e Busca (BST vs AVL) para cada ordem ---
for ordem in ["ORDENADA", "ALEATORIA"]:
    # Ordena os dados
    bst = sorted(dados[ordem]["BST"])
    avl = sorted(dados[ordem]["AVL"])

    n_bst = [x[0] for x in bst]
    ins_bst = [x[1] for x in bst]
    bus_bst = [x[2] for x in bst]

    n_avl = [x[0] for x in avl]
    ins_avl = [x[1] for x in avl]
    bus_avl = [x[2] for x in avl]

    # Garante que N é o mesmo para BST e AVL
    n = np.array(n_bst)
    largura = 0.2
    x = np.arange(len(n))

    # --- Inserção ---
    plt.figure(figsize=(8, 5))
    plt.bar(x - largura/2, ins_bst, largura, label='BST - Inserção')
    plt.bar(x + largura/2, ins_avl, largura, label='AVL - Inserção')
    plt.xticks(x, n)
    plt.xlabel('Quantidade de Streams')
    plt.ylabel('Tempo de Inserção (s)')
    plt.title(f'Comparação de Inserção - {ordem}')
    plt.legend()
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.show()

    # --- Busca ---
    plt.figure(figsize=(8, 5))
    plt.bar(x - largura/2, bus_bst, largura, label='BST - Busca')
    plt.bar(x + largura/2, bus_avl, largura, label='AVL - Busca')
    plt.xticks(x, n)
    plt.xlabel('Quantidade de Streams')
    plt.ylabel('Tempo de Busca (s)')
    plt.title(f'Comparação de Busca - {ordem}')
    plt.legend()
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.show()

# --- Comparação da Inserção e Busca: Ordenada x Aleatória ---
for tipo in ["BST", "AVL"]:
    # Ordena os dados de cada ordem
    ord_bst = sorted(dados["ORDENADA"][tipo])
    ale_bst = sorted(dados["ALEATORIA"][tipo])

    n_ord = [x[0] for x in ord_bst]
    ins_ord = [x[1] for x in ord_bst]
    bus_ord = [x[2] for x in ord_bst]

    n_ale = [x[0] for x in ale_bst]
    ins_ale = [x[1] for x in ale_bst]
    bus_ale = [x[2] for x in ale_bst]

    n = np.array(n_ord)
    largura = 0.2
    x = np.arange(len(n))

    # --- Inserção Ordenada x Aleatória ---
    plt.figure(figsize=(8, 5))
    plt.bar(x - largura/2, ins_ord, largura, label=f'{tipo} - Inserção Ordenada')
    plt.bar(x + largura/2, ins_ale, largura, label=f'{tipo} - Inserção Aleatória')
    plt.xticks(x, n)
    plt.xlabel('Quantidade de Streams')
    plt.ylabel('Tempo de Inserção (s)')
    plt.title(f'Comparação da Inserção - {tipo} (Ordenada x Aleatória)')
    plt.legend()
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.show()

    # --- Busca Ordenada x Aleatória ---
    plt.figure(figsize=(8, 5))
    plt.bar(x - largura/2, bus_ord, largura, label=f'{tipo} - Busca Ordenada')
    plt.bar(x + largura/2, bus_ale, largura, label=f'{tipo} - Busca Aleatória')
    plt.xticks(x, n)
    plt.xlabel('Quantidade de Streams')
    plt.ylabel('Tempo de Busca (s)')
    plt.title(f'Comparação da Busca - {tipo} (Ordenada x Aleatória)')
    plt.legend()
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.show()
