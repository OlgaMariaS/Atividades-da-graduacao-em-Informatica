def QuickSort(lista):

    def quicksort(lista):
        if len(lista) <= 1:
            return lista
        pivot = lista[len(lista) // 2]
        menores = [x for x in lista if x < pivot]
        iguais = [x for x in lista if x == pivot]
        maiores = [x for x in lista if x > pivot]
        return quicksort(menores) + iguais + quicksort(maiores)
    
    lista = quicksort(lista)
    return lista
