from sys    import argv
from lexico import lexer
from parser import parser #, make_parser
from utils  import calculate_column

# TESTAR SOMENTE O LÉXICO
# if len(argv) == 2:
#     with open(argv[1], 'r') as input:
#         data = input.read()
#         lexer.input(data)

#         while True:
#             tok = lexer.token() # return next token
#             if not tok:
#                 break
#             col = calculate_column(tok, lexer)
#             print(f"<{tok.type}, {tok.value!r}> na linha: {tok.lineno}, coluna:{col}")
# else:
#     print('Necessário informar o arquivo .tascal')

if len(argv) == 2:
    with open(argv[1], 'r') as input:
        data = input.read()
        parser.parse(data, lexer=lexer)

else:
    print('Necessário informar o arquivo .tascal')

# python main.py ProgramasTascalTeste/P1.

# if __name__ == "__main__":
#     data = sys.stdin.read()
#     parser = make_parser()
#     parser.parse(data, lexer=make_lexer())
#     if not tem_erro:
#         print('Parabéns, seu programa está correto!')