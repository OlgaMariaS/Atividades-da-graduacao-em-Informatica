def RadixSort(lista):
    tamanho_maximo = max(len(s) for s in lista)

    def counting_sort(lista, posicao):
        n = len(lista)
        output = ["" for _ in range(n)]
        count = [0] * 256 # ASCII

        # Contar ocorrências de cada caractere na posição especificada
        for string in lista:
            index = ord(string[posicao]) if posicao < len(string) else 0
            count[index] += 1

        # Calcular posições acumuladas
        for i in range(1, 256):
            count[i] += count[i - 1]

        # Construir a saída, percorrendo de trás para frente para estabilidade
        for string in reversed(lista):
            index = ord(string[posicao]) if posicao < len(string) else 0
            output[count[index] - 1] = string
            count[index] -= 1

        # Copiar a saída de volta para a lista original
        for i in range(n):
            lista[i] = output[i]

    # Ordenar da última posição para a primeira
    for posicao in range(tamanho_maximo - 1, -1, -1):
        counting_sort(lista, posicao)

    return lista
