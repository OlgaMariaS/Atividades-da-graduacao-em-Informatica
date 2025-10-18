from sys import argv
from lexico import lexer
from utils import calculate_column

if len(argv) == 2:
    with open(argv[1], 'r') as entrada:
        data = entrada.read()
        lexer.input(data)

        while True:
            tok = lexer.token() # return next token
            if not tok:
                break
            col = calculate_column(tok, lexer)
            print(f"<{tok.type}, {tok.value!r}> na linha: {tok.lineno}, coluna:{col}")
else:
    print('Necessário informar o arquivo .tascal')

# aqui vai ter a conexão com o yacc (sintatico)
# trabalhar na tabela de simbolos
# Lembrando que alguns casoso lexico vai gerar para o sintatico dar o erro


# PRA TABELA DE SIMBOLOS USAR DICT
# python main.py ProgramasTascalTeste/P1.tascal