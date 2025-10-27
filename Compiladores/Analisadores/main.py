from sys    import argv
from lexico import make_lexer
from parser import make_parser

if __name__ == "__main__":
    if len(argv) == 2:
        with open(argv[1], 'r') as input:
            data = input.read()
            parser = make_parser()
            lexer=make_lexer()
            parser.parse(data, lexer)
            
    else:
        print('Necessário informar o arquivo .tascal')