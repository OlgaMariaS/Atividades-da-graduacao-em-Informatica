import sys, os
from pprint import pprint
from lexico import make_lexer
from parser import make_parser
from printer import ImpressoraAST
from semantic import AnalisadorSemantico
from codegen import GeradorDeCodigo

def imprimir_modo_uso():
    print("Modo de uso: python main.py <flag> arquivo_entrada", file=sys.stderr)
    print("Flags:", file=sys.stderr)
    print("  -l : Executa apenas a análise léxica.", file=sys.stderr)
    print("  -p : Executa as análises léxica e sintática.", file=sys.stderr)
    print("  -pp : Executa as análises léxica e sintática e imprime e AST (se não houver erros).", file=sys.stderr)
    print("  -s : Executa as análises léxica, sintática e semântica.", file=sys.stderr)
    print("  -g : Executa o pipeline completo e gera o código.", file=sys.stderr)

def main():
    
    if len(sys.argv) != 3:
        imprimir_modo_uso()
        sys.exit(0)
        
    flag = sys.argv[1]
    
    try:
        with open(sys.argv[2], 'r') as input_file:
            data = input_file.read()
    except Exception as e:
        print(f"Erro ao ler stdin: {e}", file=sys.stderr)
        sys.exit(0)

    # Analisador léxico
    lexer = make_lexer()
    
    # Execução para -l
    if flag == '-l':
        lexer.input(data)
        while True:
            tok = lexer.token()
            if not tok:
                break
        
        if lexer.tem_erro:
            sys.exit(0)
        else:
            print("SUCESSO: Análise léxica concluída.", file=sys.stderr)
        return 

    # Analisador sintático
    parser = make_parser() 
    raiz_ast = parser.parse(data, lexer=lexer)

    if parser.tem_erro or lexer.tem_erro:
        sys.exit(0)
    
    # Execução para -p
    if flag == '-p':
        print("SUCESSO: Análises léxica e sintática concluídas.", file=sys.stderr)
        return 
    
    # Execução para -pp
    if flag == '-pp':
        print("SUCESSO: Análises léxica e sintática concluídas.", file=sys.stderr)
        print("\n--- AST ---")
        impressora = ImpressoraAST()
        impressora.visita(raiz_ast)
        return

    # Analisador semântico
    analisadorSem = AnalisadorSemantico()
    analisadorSem.visita(raiz_ast) 
    
    if analisadorSem.tem_erro:
        print("Erros semânticos:", file=sys.stderr)
        for erro in analisadorSem.erros:
            print(f"- {erro}", file=sys.stderr)
        sys.exit(0)
    
    # Execução para -s
    if flag == '-s':
        print("SUCESSO: Análises léxica, sintática e semântica concluídas.", file=sys.stderr)
        return 

    # Execução para -g
    if flag == '-g':
        gerador = GeradorDeCodigo()
        gerador.visita(raiz_ast)

        if gerador.tem_erro:
            print("ERRO DE GERAÇÃO:", file=sys.stderr)
            for erro in gerador.erros:
                print(f"- {erro}", file=sys.stderr)
            sys.exit(0)

        # --- salvar arquivo .mep ---
        entrada = os.path.basename(sys.argv[2])
        nome_saida = os.path.splitext(entrada)[0] + ".mep"
        caminho_saida = os.path.join("codigos_mepa", nome_saida)

        try:
            with open(caminho_saida, "w") as out:
                for instrucao in gerador.codigo:
                    out.write(instrucao + "\n")
            print(f"SUCESSO: Geração de código  do '{nome_saida}' concluída.", file=sys.stderr)
        except Exception as e:
            print(f"ERRO ao salvar arquivo '{nome_saida}': {e}", file=sys.stderr)
        return

    # Flag inválida
    print(f"ERRO: Flag '{flag}' desconhecida.", file=sys.stderr)
    imprimir_modo_uso()
    sys.exit(0)

if __name__ == "__main__":
    main()