from sys import argv
import lexico
import parser

if __name__ == "__main__":
    if len(argv) == 2:
        with open(argv[1], 'r') as input_file:
            data = input_file.read()
            
            lexer = lexico.make_lexer()
            parser, existe_erro = parser.make_parser()

            # Executa a análise
            parser.parse(data, lexer)

            if not existe_erro:
                print('Programa executado com sucesso!')
            else:
                print('Erros encontrados durante a execução.')
    else:
        print('Necessário informar o arquivo .tascal')
