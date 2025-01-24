import sys

"""
Implementação do algoritmo de Prim para encontrar a Árvore Geradora Mínima (AGM).

Parametros de entrada:
    -grafo: Matriz que representa o grafo ponderado;
    -n: Número de vértices no grafo;

Retorno:
    - Lista de arestas que formam a árvore geradora mínima.
"""

def prim(grafo, n):
    F = []  # Armazena o conjunto de arestas da AGM
    prox = [-1] * n  # Próximos vértices 
    visitado = [False] * n  # Marca os vértices que já estão na árvore
    contador = 0  # Contador de arestas 

    # Escolhe (u, v) como a aresta de menor peso inicialmente
    menor_peso = sys.maxsize

    u, v = -1, -1
    for i in range(n):
        for j in range(n):
            if grafo[i][j] != 0 and grafo[i][j] < menor_peso:
                menor_peso = grafo[i][j]
                u, v = i, j

    # Adiciona a aresta inicial na árvore
    F.append((u, v))
    visitado[u] = True
    visitado[v] = True

    # Define prox(i)
    for i in range(n):
        if not visitado[i]:  # Apenas para vértices não visitados
            if grafo[i][u] < grafo[i][v] and grafo[i][u] != 0:
                prox[i] = u
            elif grafo[i][v] != 0:
                prox[i] = v

    while contador < n - 2:
        # Escolhe j tal que prox[j] ≠ -1 e c(j, prox[j]) é mínimo
        j = -1
        menor_peso = sys.maxsize
        for i in range(n):
            if prox[i] != -1 and grafo[i][prox[i]] < menor_peso:
                menor_peso = grafo[i][prox[i]]
                j = i

        # Adiciona a aresta correspondente na árvore
        F.append((j, prox[j]))
        visitado[j] = True
        prox[j] = -1  # Remove j como próximo

        # Atualiza prox(i)
        for i in range(n):
            if not visitado[i] and grafo[i][j] != 0:
                if prox[i] == -1 or grafo[i][j] < grafo[i][prox[i]]:
                    prox[i] = j

        contador += 1

    return F

# Representação do grafo como matriz
grafo = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
]
# Número de vértices
n = len(grafo)  

# Resultado da árvore geradora mínima pela função de Prim
agm = prim(grafo, n)
print("Árvore Geradora Mínima:", agm)
