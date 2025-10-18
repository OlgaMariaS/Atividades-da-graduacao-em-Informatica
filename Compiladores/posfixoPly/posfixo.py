# posfixo.py
import sys
import ply.lex as lex
import ply.yacc as yacc

# ---------- LEXER ----------
tokens = ('IDENT', 'MAIS', 'MENOS', 'ASTERISCO', 'DIV')

t_MAIS      = r'\+'
t_MENOS     = r'-'
t_ASTERISCO = r'\*'
t_DIV       = r'/'

def t_IDENT(t):
    r'a'
    return t

t_ignore = ' \t\n'

def t_error(t):
    print(f"ERRO léxico - símbolo ilegal '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()

# ---------- PARSER ----------
saida = [] # lista que armazena a expressão posfixa

def p_expr_mais(p):
    "expr : expr MAIS termo"
    saida.append('+')

def p_expr_menos(p):
    "expr : expr MENOS termo"
    saida.append('-')

def p_expr_termo(p):
    "expr : termo"
    pass

def p_termo_vezes(p):
    "termo : termo ASTERISCO fator"
    saida.append('*')

def p_termo_div(p):
    "termo : termo DIV fator"
    saida.append('/')

def p_termo_fator(p):
    "termo : fator"
    pass

def p_fator_ident(p):
    "fator : IDENT"
    saida.append('A')

def p_error(t):
    if t:
        print(f"ERRO de sintaxe perto de '{t.value}'")
    else:
        print("ERRO de sintaxe no EOF")

parser = yacc.yacc(start='expr')

# ---------- MAIN ----------
def main():
    data = sys.stdin.read()
    parser.parse(data, lexer=lexer)
    print("".join(saida))

if __name__ == "__main__":
    main()
