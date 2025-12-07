import sys
import AST as ast
import ply.yacc as yacc
from lexico import tokens, make_lexer

parser = None

precedence = (
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    ('right', 'UMINUS'),
    ('right', 'NOT')
)

# ================== Regras de produção com AST ======================= #
def p_programa(p):
    "programa : PROGRAM ID ';' bloco DOT"
    p[0] = ast.Programa(nome=p[2], bloco=p[4])

def p_bloco(p):
    '''bloco : VAR secao_declaracao_vars comando_composto
             | comando_composto'''
    if len(p) == 4:
        p[0] = ast.Bloco(declaracoes=p[2], comando=p[3])
    else:
        p[0] = ast.Bloco(declaracoes=[], comando=p[1])

def p_secao_declaracao_vars_uma(p):
    "secao_declaracao_vars : declaracao_vars ';'"
    p[0] = [p[1]]

def p_secao_declaracao_vars_varias(p):
    "secao_declaracao_vars : declaracao_vars ';' secao_declaracao_vars"
    p[0] = [p[1]] + p[3]

def p_declaracao_vars(p):
    "declaracao_vars : lista_ids ':' tipo"
    p[0] = ast.Declaracao(nomes=p[1], tipo=p[3])

def p_id_um(p):
    "lista_ids : ID"
    p[0] = [p[1]]

def p_id_varios(p):
    "lista_ids : ID ',' lista_ids"
    p[0] = [p[1]] + p[3]

def p_tipo(p):
    '''tipo : BOOL 
            | INT'''
    p[0] = p[1]

def p_comando_composto(p):
    "comando_composto : BEGIN lista_comandos END"
    p[0] = ast.BlocoCmds(lista_cmds=p[2])

def p_lista_comandos_um(p):
    "lista_comandos : comando"
    p[0] = [p[1]]

def p_lista_comandos_varios(p):
    "lista_comandos : comando ';' lista_comandos"
    p[0] = [p[1]] + p[3]

def p_comando(p):
    '''comando : atribuicao
               | condicional
               | repeticao
               | leitura
               | escrita
               | comando_composto'''
    p[0] = p[1]

def p_atribuicao(p):
    "atribuicao : ID ATRIB expr"
    p[0] = ast.Atribuicao(
        id=ast.CalcId(nome=p[1]),
        calculo=p[3]
    )

def p_condicional(p):
    '''condicional : IF expr THEN comando %prec IFX
                   | IF expr THEN comando ELSE comando'''
    if len(p) == 5:
        p[0] = ast.Condicional(condicao=p[2], bloco_then=p[4], bloco_else=None)
    else:
        p[0] = ast.Condicional(condicao=p[2], bloco_then=p[4], bloco_else=p[6])

def p_repeticao(p):
    "repeticao : WHILE expr DO comando"
    p[0] = ast.Repeticao(condicao=p[2], corpo=p[4])

def p_leitura(p):
    "leitura : READ '(' lista_ids ')'"
    p[0] = ast.Leitura(ids=[ast.CalcId(nome=n) for n in p[3]])

def p_escrita(p):
    "escrita : WRITE '(' lista_expr ')'"
    p[0] = ast.Escrita(exprs=p[3])

def p_lista_expr_uma(p):
    "lista_expr : expr"
    p[0] = [p[1]]

def p_lista_expr_varias(p):
    "lista_expr : expr ',' lista_expr"
    p[0] = [p[1]] + p[3]

def p_expr(p):
    '''expr : expr_simples
            | expr_simples relacao expr_simples'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = ast.CalculoBinario(esq=p[1], op=p[2], dir=p[3])

def p_relacao(p):
    '''relacao : '='
               | DIF
               | '<'
               | LESS
               | '>'
               | GREATER'''
    p[0] = p[1]

def p_expr_simples(p):
    "expr_simples : termo lista_termos"
    esq = p[1]
    lista = p[2]
    for op, dir in lista:
        esq = ast.CalculoBinario(esq=esq, op=op, dir=dir)
    p[0] = esq

def p_lista_termos_vazio(p):
    "lista_termos : "
    p[0] = []

def p_lista_termos_varios(p):
    "lista_termos : operador_termo termo lista_termos"
    p[0] = [(p[1], p[2])] + p[3]

def p_operador_termo(p):
    '''operador_termo : '+'
                      | '-'
                      | OR'''
    p[0] = p[1]

def p_termo(p):
    "termo : fator lista_fatores"
    esq = p[1]
    lista = p[2]
    for op, f in lista:
        esq = ast.CalculoBinario(esq=esq, op=op, dir=f)
    p[0] = esq

def p_lista_fatores_vazio(p):
    "lista_fatores : "
    p[0] = []

def p_lista_fatores_varios(p):
    "lista_fatores : operador_fator fator lista_fatores"
    p[0] = [(p[1], p[2])] + p[3]

def p_operador_fator(p):
    '''operador_fator : '*'
                      | DIV
                      | AND'''
    p[0] = p[1]

def p_fator_id(p):
    "fator : ID"
    p[0] = ast.CalcId(nome=p[1])

def p_fator_num(p):
    "fator : NUM"
    p[0] = ast.CalcConstNum(valor=p[1])

def p_fator_log(p):
    '''fator : FALSE 
             | TRUE'''
    p[0] = ast.CalcConstBool(valor=(p[1] == "true"))

def p_fator_expr(p):
    "fator : '(' expr ')'"
    p[0] = p[2]

def p_fator_not(p):
    "fator : NOT fator"
    p[0] = ast.CalculoUnario(op='not', calculo=p[2])

def p_fator_neg(p):
    "fator : NEG fator %prec UMINUS"
    p[0] = ast.CalculoUnario(op='-', calculo=p[2])

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