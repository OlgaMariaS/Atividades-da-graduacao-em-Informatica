import sys
import ply.yacc as yacc
from lexico import tokens, reserved, make_lexer

parser = None

precedence = (
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    ('right', 'UMINUS'),
    ('right', 'NOT')
)

# ==================Regras de produção da gramática======================= # 
def p_programa(p):
    "programa : PROGRAM ID ';' bloco DOT"

def p_bloco(p):
    '''bloco : VAR secao_declaracao_vars comando_composto
             | comando_composto'''

def p_secao_declaracao_vars_uma(p):
    "secao_declaracao_vars : declaracao_vars ';'"

def p_secao_declaracao_vars_varias(p):
    "secao_declaracao_vars : declaracao_vars ';' secao_declaracao_vars"

def p_declaracao_vars(p):
    "declaracao_vars : lista_ids ':' tipo"

def p_id_um(p):
    "lista_ids : ID"

def p_id_varios(p):
    "lista_ids : ID ',' lista_ids"

def p_tipo (p):
    '''tipo : BOOL 
            | INT'''

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
    '''condicional : IF expr THEN comando %prec IFX
                   | IF expr THEN comando ELSE comando'''

def p_repeticao(p):
    "repeticao : WHILE expr DO comando"

def p_leitura(p):
    "leitura : READ '(' lista_ids ')'"

def p_escrita(p):
    "escrita : WRITE '(' lista_expr ')' "

# Retorna um lista de expressões
def p_lista_expr_uma(p):
    "lista_expr : expr"

def p_lista_expr_varias(p):
    "lista_expr : expr ',' lista_expr"

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

def p_termos_varios(p):
    "lista_termos : operador_termo termo lista_termos"

def p_operador_termo(p):
    '''operador_termo : '+'
                      | '-'
                      | OR '''
    
def p_termo(p):
    "termo : fator lista_fatores"
    
def p_fator_vazio(p):
    "lista_fatores : "

def p_fator_varios(p):
    "lista_fatores : operador_fator fator lista_fatores"

def p_operador_fator(p):
    '''operador_fator : '*'
                      | DIV
                      | AND '''
         
def p_fator(p):
    '''fator : fator_id
             | fator_num
             | fator_log
             | fator_expr
             | fator_not
             | fator_neg '''

def p_fator_id(p):
    "fator_id : ID"

def p_fator_num(p):
    "fator_num : NUM"

def p_fator_log(p):
    '''fator_log : FALSE 
                 | TRUE'''

def p_fator_expr(p):
    "fator_expr : '(' expr ')'"

def p_fator_not(p):
    "fator_not : NOT fator"

def p_fator_neg(p):
    "fator_neg : NEG fator %prec UMINUS"

# =========================================================== #
def p_error(p):
    global parser
    if p:
        print(f"Erro sintático: Token inesperado: {p.type} ('{p.value}') na linha {p.lineno}", file=sys.stderr)
    else:
        print("Erro sintático: Fim inesperado do arquivo (EOF).", file=sys.stderr)
    parser.tem_erro = True

# Instancia o parser
def make_parser(start='programa'):
    global parser 
    parser = yacc.yacc(start=start)
    parser.tem_erro = False
    return parser

# Testar somente parser
if __name__ == "__main__":
    data = sys.stdin.read()
    parser = parser.make_parser()
    parser.parse(data, lexer=make_lexer())
    if not parser.tem_erro: 
        print('Programa executado com sucesso!')