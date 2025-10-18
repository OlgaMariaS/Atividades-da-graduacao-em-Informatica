# posfixo3.py
import sys
from enum import Enum
import ply.lex as lex
import ply.yacc as yacc

# ---------- LEXER ----------
tokens = ('IDENT', 'MAIS', 'MENOS', 'ASTERISCO', 'DIV', 'AND', 'OR')

t_MAIS      = r'\+'
t_MENOS     = r'-'
t_ASTERISCO = r'\*'
t_DIV       = r'/'

def t_AND(t):
    r'and'
    return t

def t_OR(t):
    r'or'
    return t

def t_IDENT(t):
    r'a|b'
    return t

t_ignore = ' \t\n'

# Erro léxico
def t_error(t):
    print(f"ERRO léxico - símbolo ilegal '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()

# ---------- PARSER ----------
saida = [] # lista que armazena a expressão posfixa

# Tipos 
class Tipo(Enum):
    INT  = 1
    BOOL = 2

# Funções de erro semântico
def nomeTipo(t: Tipo) -> str:
    if t is Tipo.INT:  return 'int'
    if t is Tipo.BOOL: return 'bool'
    return "erro"

def erro_semantico(op, le: Tipo, ld: Tipo, esperado: str):
    sys.stderr.write(
        f"ERRO SEMÂNTICO: operador '{op}' incompatível com operandos ({nomeTipo(le)}, {nomeTipo(ld)}). "
        f"Esperado: {esperado}\n"
    )

# Regras
def p_exprl_and(p):
    "exprl : exprl AND expr"
    if p[1] is not Tipo.BOOL or p[3] is not Tipo.BOOL:
        erro_semantico('and', p[1], p[3], '(bool, bool)')
    p[0] = Tipo.BOOL
    saida.append(' and ')

def p_exprl_or(p):
    "exprl : exprl OR expr"
    if p[1] is not Tipo.BOOL or p[3] is not Tipo.BOOL:
        erro_semantico('or', p[1], p[3], '(bool, bool)')
    p[0] = Tipo.BOOL
    saida.append(' or ')

def p_exprl_expr(p):
    "exprl : expr"
    p[0] = p[1]

def p_expr_soma(p):
    "expr : expr MAIS termo"
    if p[1] is not Tipo.INT or p[3] is not Tipo.INT:
        erro_semantico('+', p[1], p[3], '(int, int)')
    p[0] = Tipo.INT
    saida.append('+')

def p_expr_sub(p):
    "expr : expr MENOS termo"
    if p[1] is not Tipo.INT or p[3] is not Tipo.INT:
        erro_semantico('-', p[1], p[3], '(int, int)')
    p[0] = Tipo.INT
    saida.append('-')

def p_expr_termo(p):
    "expr : termo"
    p[0] = p[1]

def p_termo_mul(p):
    "termo : termo ASTERISCO fator"
    if p[1] is not Tipo.INT or p[3] is not Tipo.INT:
        erro_semantico('*', p[1], p[3], '(int, int)')
    p[0] = Tipo.INT
    saida.append('*')

def p_termo_div(p):
    "termo : termo DIV fator"
    if p[1] is not Tipo.INT or p[3] is not Tipo.INT:
        erro_semantico('/', p[1], p[3], '(int, int)')
    p[0] = Tipo.INT
    saida.append('/')

def p_termo_fator(p):
    "termo : fator"
    p[0] = p[1]

def p_fator_ident(p):
    "fator : IDENT"
    if p[1] == 'a':
        p[0] = Tipo.INT
        saida.append('A')
    else:
        p[0] = Tipo.BOOL
        saida.append('B')

# Erro sintático
def p_error(t):
    if t:
        print(f"ERRO de sintaxe perto de '{t.value}'")
    else:
        print("ERRO de sintaxe no EOF")

parser = yacc.yacc(start='exprl')

# ---------- MAIN ----------
def main():
    data = sys.stdin.read()
    parser.parse(data, lexer=lexer)
    print("".join(saida))

if __name__ == "__main__":
    main()
