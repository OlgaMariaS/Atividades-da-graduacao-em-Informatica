from sys import argv
from lexico import lexer, calcula_coluna

if len(argv) == 2:
    with open(argv[1], 'r') as entrada:
        data = entrada.read()
        lexer.input(data)

        while True:
            tok = lexer.token()
            if not tok:
                break
            col = calcula_coluna(tok, lexer)
            print(f"<{tok.type}, {tok.value!r}> na linha: {tok.lineno}, coluna:{col}") # !r -> imprima a representação repr() do valor, em vez da conversão str()
else:
    print('Faltou o nome do arquivo a ser escaneado!')
