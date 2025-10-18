import sys
from enum import Enum
import ply.yacc as yacc
from lexico import lexer
from utils import calculate_column

class Tipo(Enum):
    INT  = 0
    BOOL = 1

# Funções de erro semântico
def nomeTipo(t: Tipo) -> str:
    if t is Tipo.INT:  return 'int'
    if t is Tipo.BOOL: return 'bool'
    return "erro"

precedence = (
    ('nonassoc', 'LESS', 'GREATER')
    ('nonassoc', 'ELSE'),
    ('left', '+', '-'),
    ('left', '*', '/'),
    ('right', 'UMINUS'),
)

def p_programa(p):
    "programa : PROGRAM ID ';' bloco '.'"

# DÚVIDA DE VAR SOMENTE UM VEZ
def p_bloco(p):
    '''bloco : secao_declaracao_vars comando_composto
             | comando_composto'''

def p_secao_declaracao_vars_uma(p):
    "secao_declaracao_vars : VAR declaracao_vars ';'"

def p_secao_declaracao_vars_varias(p):
    "secao_declaracao_vars : VAR declaracao_vars ';' secao_declaracao_vars"

def p_declaracao_vars(p):
    "declaracao_vars : lista_ids ':' tipo"

def p_lista_ids(p):
    "lista_ids : ids"

def p_id_um(p):
    "ids : ID" 

def p_id_varios(p):
    "ids : ID ',' ids"

def p_tipo (p):
    '''tipo : BOOL 
            | INT'''

def p_logico(p):
    '''logico : TRUE 
              | FALSE'''

def p_comando_composto(p):
    "comando_composto : BEGIN lista_comandos END"

def p_lista_comandos_um(p):
    "lista_comandos : comando"

def p_lista_comandos_varios(p):
    "lista_comandos : comando ';' lista_comandos"

def p_comando (p):
    '''comando : atribuicao
               | condicional
               | repeticao
               | leitura
               | escrita
               | comando_composto'''
    
def p_atribuicao(p):
    "atribuicao : ID ATRIB expr"

def p_condicional(p):
    '''condicional : IF expr THEN comando
                   | IF expr THEN comando ELSE comando'''

def p_repeticao(p):
    "repeticao : WHILE expr DO comando "

def p_leitura(p):
    "leitura : READ '(' lista_ids ')' "

def p_escrita(p):
    "escrita : WRITE '(' lista_expr ')' " 

def p_lista_expr(p):
    "lista_expr : expressao"

def p_lista_expr_uma(p):
    "expressao : expr"

def p_lista_expr_varias(p):
    "expressao : expressao expr ',' "

def p_expr(p):
    '''expr : expr_simples
            | expr_simples relacao expr_simples'''

def p_relacao(p):
    '''relacao : '='
               | DIF
               | '<'
               | LESS
               | '>'
               | GREATER '''

def p_expr_simples(p):
    "expr_simples : termo lista_termos"
    
def p_termo_vazio(p):
    "lista_termos : "
    p[0] = []

def p_termos_varios(p):
    "lista_termos : lista_termos operador_termo termo"
    p[0] = p[1] + [(p[2], p[3])] 

def p_operador_termo(p):
    '''operador_termo : '+'
                      | '-'
                      | OR '''
    
def p_termo(p):
    "termo : fator lista_fatores"
    
def p_fator_vazio(p):
    "lista_fatores : "
    p[0] = []

def p_fator_varios(p):
    "lista_fatores : lista_fatores operador_fator fator"
    p[0] = p[1] + [(p[2], p[3])] 

def p_operador_fator(p):
    '''operador_fator : '*'
                      | '/'
                      | AND '''
        
def p_fator_id(p):
    "fator : ID"

def p_fator_num(p):
    "fator : NUM"

def p_fator_log(p):
    "fator : logico"

def p_fator_expr(p):
    "fator : '(' expr ')'"

def p_fator_not(p):
    "fator : NOT fator"

def p_fator_neg(p):
    "fator : '-' fator %prec UMINUS"

# Erro sintático
def p_error(p):
    if p:
        col = calculate_column(p)
        print(f"ERRO SINTÁTICO: Símbolo inesperado {p.value!r} na linha {p.lineno}, coluna {col}")
    else:
        print("ERRO SINTÁTICO: fim inesperado de arquivo (EOF)")

def erro_semantico(token, mensagem): # mensagem?
    col = calculate_column(token)
    print(f"ERRO SEMÂNTICO: {mensagem} na linha {token.lineno}, coluna {col}")

parser = yacc.yacc(start='program')

# ---------- MAIN ----------
def main():
    data = sys.stdin.read()
    parser.parse(data, lexer=lexer)

if __name__ == "__parser__":
    main()