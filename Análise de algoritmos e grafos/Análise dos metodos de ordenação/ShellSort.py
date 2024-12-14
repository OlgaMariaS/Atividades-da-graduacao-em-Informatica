import pandas as pd

def ShellSort(arquivo_xls, coluna):
    dados = pd.read_excel(arquivo_xls)
    lista = dados[coluna].tolist()

    n = len(lista)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = lista[i]
            j = i
            while j >= gap and lista[j - gap] > temp:
                lista[j] = lista[j - gap]
                j -= gap
            lista[j] = temp
        gap //= 2

    dados[coluna] = lista
    return dados
