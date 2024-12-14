import pandas as pd

def MergeSort(arquivo_xls, coluna):
    dados = pd.read_excel(arquivo_xls)
    lista = dados[coluna].tolist()

    def mergesort(lista):
        if len(lista) > 1:
            meio = len(lista) // 2
            esq = lista[:meio]
            dir = lista[meio:]

            mergesort(esq)
            mergesort(dir)

            i = j = k = 0
            while i < len(esq) and j < len(dir):
                if esq[i] < dir[j]:
                    lista[k] = esq[i]
                    i += 1
                else:
                    lista[k] = dir[j]
                    j += 1
                k += 1

            while i < len(esq):
                lista[k] = esq[i]
                i += 1
                k += 1

            while j < len(dir):
                lista[k] = dir[j]
                j += 1
                k += 1

    mergesort(lista)
    dados[coluna] = lista
    return dados
