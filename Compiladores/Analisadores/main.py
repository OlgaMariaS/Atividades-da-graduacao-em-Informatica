from sys    import argv
import lexico
import parser as sintatico

if __name__ == "__main__":
    if len(argv) == 2:
        with open(argv[1], 'r') as input:
            data = input.read()
            parser = sintatico.make_parser()
            lexer = lexico.make_lexer()
            parser.parse(data, lexer)
            
            if (lexico.existe_erro == False) and (sintatico.existe_erro == False):
                print('Programa executado com sucesso!')
    else:
        print('Necessário informar o arquivo .tascal')