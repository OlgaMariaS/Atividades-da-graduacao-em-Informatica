import pandas as pd

def InserctionSort(arquivo_xls, coluna):
    """
    Ordena os dados do arquivo XLS pelo método de Inserção Direta (Insertion Sort).
    :param arquivo_xls: Caminho do arquivo XLS.
    :param coluna: Nome da coluna para ordenação.
    :return: DataFrame ordenado.
    """
    # Carregar o arquivo XLS
    dados = pd.read_excel(arquivo_xls)
    lista = dados[coluna].tolist()

    # Implementação do Insertion Sort
    for i in range(1, len(lista)):
        chave = lista[i]
        j = i - 1
        while j >= 0 and lista[j] > chave:
            lista[j + 1] = lista[j]
            j -= 1
        lista[j + 1] = chave

    # Atualizar o DataFrame com a coluna ordenada
    dados[coluna] = lista
    return dados
