from sys import argv
from lexico1 import lexico, calcula_coluna

if len(argv) == 2:
    with open(argv[1], 'r') as entrada:
        data = entrada.read()

        # lexico.line_start = 0
        lexico.input(data)

        while True:
            tok = lexico.token()
            if not tok:
                break
            col = calcula_coluna(tok, lexico)
            print(f"<{tok.type}, {tok.value!r}> na linha: {tok.lineno}, coluna:{col}") # !r -> imprima a representação repr() do valor, em vez da conversão str()
            # print(f"<{tok.type}, {tok.value!r}> na linha {tok.lineno}, posição {tok.lexpos}")
else:
    print('Faltou o nome do arquivo a ser escaneado!')

# O método input() reinicia o analisador e armazena uma nova string de entrada. 
# O método token() retorna o próximo token como uma instância de LexToken em
# caso de sucesso ou None se o fim da entrada for alcançado. Objetos LexToken possuem os
# atributos type, value, lineno e lexpos.


# python teste_lexico.py codigo_exemplo.tas 