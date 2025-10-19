from sys    import argv
from lexico import lexer
from parser import parser
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

