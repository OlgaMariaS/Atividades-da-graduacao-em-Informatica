import pandas as pd

def SelectionSort(arquivo_xls, coluna):
    """
    Ordena os dados do arquivo XLS pelo método de Seleção Direta (Selection Sort).
    :param arquivo_xls: Caminho do arquivo XLS.
    :param coluna: Nome da coluna para ordenação.
    :return: DataFrame ordenado.
    """
    # Carregar o arquivo XLS
    dados = pd.read_excel(arquivo_xls)
    lista = dados[coluna].tolist()

    # Implementação do Selection Sort
    n = len(lista)
    for i in range(n):
        # Encontra o índice do menor elemento a partir de i
        menor_indice = i
        for j in range(i + 1, n):
            if lista[j] < lista[menor_indice]:
                menor_indice = j

        # Troca o elemento atual com o menor elemento encontrado
        lista[i], lista[menor_indice] = lista[menor_indice], lista[i]

    # Atualizar o DataFrame com a coluna ordenada
    dados[coluna] = lista
    return dados
