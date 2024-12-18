def HeapSort(lista):
    
    def heapify(lista, n, i):
        maior = i
        l = 2 * i + 1
        r = 2 * i + 2

        if l < n and lista[l] > lista[maior]:
            maior = l
        if r < n and lista[r] > lista[maior]:
            maior = r
        if maior != i:
            lista[i], lista[maior] = lista[maior], lista[i]
            heapify(lista, n, maior)

    n = len(lista)
    for i in range(n // 2 - 1, -1, -1):
        heapify(lista, n, i)
    for i in range(n - 1, 0, -1):
        lista[i], lista[0] = lista[0], lista[i]
        heapify(lista, i, 0)

    return lista
