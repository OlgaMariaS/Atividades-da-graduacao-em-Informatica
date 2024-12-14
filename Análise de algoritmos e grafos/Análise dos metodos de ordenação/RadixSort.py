import pandas as pd

def RadixSort(arquivo_xls, coluna):
    dados = pd.read_excel(arquivo_xls)
    lista = dados[coluna].tolist()

    def counting_sort(lista, exp):
        n = len(lista)
        output = [0] * n
        count = [0] * 10

        for i in lista:
            index = i // exp
            count[index % 10] += 1

        for i in range(1, 10):
            count[i] += count[i - 1]

        i = n - 1
        while i >= 0:
            index = lista[i] // exp
            output[count[index % 10] - 1] = lista[i]
            count[index % 10] -= 1
            i -= 1

        for i in range(n):
            lista[i] = output[i]

    maximo = max(lista)
    exp = 1
    while maximo // exp > 0:
        counting_sort(lista, exp)
        exp *= 10

    dados[coluna] = lista
    return dados
