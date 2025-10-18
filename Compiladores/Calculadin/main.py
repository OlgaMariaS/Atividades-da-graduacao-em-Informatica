import sys
from enum import Enum
import ply.yacc as yacc
from lexer import lexer

# ---------- PARSER ----------
saida = [] # lista que armazena a expressão posfixa

# Tipos 
class Tipo(Enum):
    INT  = 1

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
# def p_exprl_and(p):
#     "exprl : exprl AND expr"
#     if p[1] is not Tipo.BOOL or p[3] is not Tipo.BOOL:
#         erro_semantico('and', p[1], p[3], '(bool, bool)')
#     p[0] = Tipo.BOOL
#     saida.append(' and ')

# def p_exprl_or(p):
#     "exprl : exprl OR expr"
#     if p[1] is not Tipo.BOOL or p[3] is not Tipo.BOOL:
#         erro_semantico('or', p[1], p[3], '(bool, bool)')
#     p[0] = Tipo.BOOL
#     saida.append(' or ')

# "<programa> ::= ‘iniciar’ ‘calculadin’ ‘:’ <lista-comandos> ‘finalizar’ ‘calculadin’ ‘.’"
def p_program(p):
    "program : INICIAR CALCULADIN : lista_comandos FINALIZAR CALCULADIN ."

def p_lista_comandos(p):
    "lista_comandos : lista_comandos comando ;"

def p_lista_comandos_vazia(p):
    "lista_comandos : empty"  # vazio

def p_comando_funct(p):
    "comando : chamada-funcao "

def p_comando_atrib(p):
    "comando : atribuicao"

def p_funcao_input(p):
    "chamada-funcao : INPUT '(' ID ')'"
    
def p_funcao_output(p):
    "chamada-funcao : OUTPUT '(' ID ')'"

def p_atrib(p):
    "atribuicao : ID = expr"

def p_expr_soma(p):
    "expr : expr '+' termo"

def p_expr_sub(p):
    "expr : expr '-' termo"

def p_expr_termo(p):
    "expr : termo"

def p_termo_mul(p):
    "termo : termo '*' fator"

def p_termo_div(p):
    "termo : termo '/' fator"

def p_termo_fator(p):
    "termo : fator"

# fator = num e id, expr
def p_fator_expr(p):
    "fator : ( expr )"

def p_fator_num(p):
    "fator : NUM"

def p_fator_id(p):
    "fator : ID"

# Erro sintático
def p_error(t):
    if t:
        print(f"ERRO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}")
        t.parser.skip(1)
    else:
        print("ERRO de sintaxe no EOF")

# def t_error(t): calcular coluna erro sintatico
#     col = calcula_coluna(t, t.lexer)
#     print(f"ERRO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}, coluna {col}")
#     t.lexer.skip(1)

parser = yacc.yacc(start='program')

# ---------- MAIN ----------
def main():
    data = sys.stdin.read()
    parser.parse(data, lexer=lexer)
    print("".join(saida))

if __name__ == "__main__":
    main()