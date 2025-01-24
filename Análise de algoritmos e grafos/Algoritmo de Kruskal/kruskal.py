# Classe Union-Find para gerenciar componentes conectados no grafo
class UnionFind:
    def __init__(self, n):
        """
        Inicializa as estruturas de dados para n vértices.
        - pai: Lista que armazena o "pai" de cada vértice.
        - rank: Lista que auxilia na união eficiente (controle da altura da árvore).
        """
        self.pai = list(range(n))  # Cada vértice é inicialmente seu próprio pai (isolado)
        self.rank = [0] * n  # Todos os vértices começam com rank 0

    def encontrar(self, u):
        """
        Encontra o representante (ou raiz) do conjunto ao qual o vértice u pertence.
        Aplica compressão de caminho para melhorar a eficiência.
        """
        if self.pai[u] != u:
            # Atualiza o pai de u para o representante direto do conjunto
            self.pai[u] = self.encontrar(self.pai[u])
        return self.pai[u]

    def unir(self, u, v):
        """
        Une os conjuntos de dois vértices, u e v, se eles estiverem em componentes diferentes.
        Usa a técnica de union by rank para manter as árvores balanceadas.
        """
        raiz_u = self.encontrar(u)
        raiz_v = self.encontrar(v)
        if raiz_u != raiz_v:  # Apenas une se os vértices não estão no mesmo conjunto
            if self.rank[raiz_u] < self.rank[raiz_v]:
                self.pai[raiz_u] = raiz_v  # Raiz com menor rank aponta para a maior
            elif self.rank[raiz_u] > self.rank[raiz_v]:
                self.pai[raiz_v] = raiz_u  # Raiz com maior rank permanece como raiz
            else:
                # Caso os ranks sejam iguais, escolhemos uma raiz arbitrária e aumentamos seu rank
                self.pai[raiz_v] = raiz_u
                self.rank[raiz_u] += 1


"""
Implementação do algoritmo de Prim para encontrar a Árvore Geradora Mínima (AGM).

Parametros de entrada:
    - n: Número de vértices no grafo.
    - arestas: Lista de arestas no formato (peso, u, v), onde u e v são os vértices.

Retorno:
- F: Lista de arestas que formam a Árvore Geradora Mínima.
"""
def kruskal(n, arestas):

    # Ordena as arestas em ordem crescente de peso
    arestas.sort()

    # Inicializa a estrutura de Union-Find
    uf = UnionFind(n)

    F = []  # Armazena o conjunto de arestas da AGM
    contador = 0  # Contador de arestas

    # Itera sobre as arestas ordenadas por peso
    for peso, u, v in arestas:
        if contador >= n - 1:
            # Se já temos (n-1) arestas, a AGM está completa
            break

        # Verifica se u e v pertencem a componentes diferentes
        if uf.encontrar(u) != uf.encontrar(v):
            # Adiciona a aresta à AGM
            F.append((min(u, v), max(u, v), peso))  # Sempre exibe menor índice primeiro
            uf.unir(u, v)  # Une as componentes conectadas por (u, v)
            contador += 1  # Incrementa o número de arestas na AGM

    return F;


"""
# Função para converter uma matriz em uma lista de arestas no formato (peso, u, v).
Considera apenas a metade superior da matriz, pois o grafo é não-direcionado.

Parâmetro:
    - matriz: Matriz de adjacência representando o grafo.

Retorna:
    - Lista de arestas no formato (peso, u, v).
"""
def matriz_para_arestas(matriz):
    arestas = []
    n = len(matriz)
    for i in range(n):
        for j in range(i + 1, n):  # Percorre apenas a metade superior
            if matriz[i][j] != 0:  # Ignora arestas inexistentes (peso 0)
                arestas.append((matriz[i][j], i, j))
    return arestas


# Grafo representado como matriz 
grafo = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
]

# Converte a matriz para lista de arestas
arestas = matriz_para_arestas(grafo)

# Número de vértices
n = len(grafo)

# Executa o algoritmo de Kruskal
agm = kruskal(n, arestas)

# Resultado da árvore geradora mínima pela função de Kruskal
print("Árvore Geradora Mínima:", agm)
