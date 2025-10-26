import ply.yacc as yacc
from enum   import Enum
from lexico import tokens
from utils  import calculate_column, TabelaSimbolos, erro_semantico

# instância da classe TabelaSimbolos
tabela_simbolos = TabelaSimbolos()

# Regras de produção da gramática: 
precedence = (
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    ('left', 'OR'),
    ('left', '+', '-'),
    ('left', '*', 'DIV', 'AND'),
    ('right', 'UMINUS'),
)

def p_programa(p):
    "programa : programa_begin bloco DOT" 

def p_programa_begin(p):
    "programa_begin : PROGRAM ID ';'" 

def p_bloco(p):
    '''bloco : secao_declaracao_vars comando_composto
             | comando_composto'''
    # se faltar bloco dá erro

def p_secao_declaracao_vars_uma(p):
    "secao_declaracao_vars : VAR declaracao_vars ';'"

def p_secao_declaracao_vars_varias(p):
    "secao_declaracao_vars : VAR declaracao_vars ';' secao_declaracao_vars"

def p_declaracao_vars(p):
    "declaracao_vars : lista_ids ':' tipo"
    # nome = p[1].value
    # tipo = p[3]
    # linha = p.lineno
    # tabela_simbolos.inserir(nome, tipo, linha)

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
    '''condicional : IF expr THEN comando %prec IFX
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

def p_termos_varios(p):
    "lista_termos : lista_termos operador_termo termo"

def p_operador_termo(p):
    '''operador_termo : '+'
                      | '-'
                      | OR '''
    
def p_termo(p):
    "termo : fator lista_fatores"
    
def p_fator_vazio(p):
    "lista_fatores : "

def p_fator_varios(p):
    "lista_fatores : lista_fatores operador_fator fator"

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
    "fator_log : logico"

def p_fator_expr(p):
    "fator_expr : '(' expr ')'"

def p_fator_not(p):
    "fator_not : NOT fator"

def p_fator_neg(p):
    "fator_neg : NEG fator %prec UMINUS"

# ============================ Produções para sinalização de erros sintáticos =============================== #
def p_programa_begin_error(p):
    "programa_begin : error ID ';' "
    erro_sintatico(p, 1, "Falta program")

def p_programa_id_error(p):
    "programa_begin : PROGRAM error ';' " 
    erro_sintatico(p, 2, "Nome do programa não encontrado")
    
def p_programa_pv_error(p):
    "programa_begin : PROGRAM ID error" 
    erro_sintatico(p, 3, "Esperado ';'")

def p_programa_dot_error(p):
    "programa : programa_begin bloco error"
    erro_sintatico(p, 3, "Esperado '.'")

def p_secao_declaracao_vars_uma_error(p):
    "secao_declaracao_vars : error declaracao_vars ';'"
    erro_sintatico(p, 1, "Necessário VAR para declarar váriaveis")
    
def p_secao_declaracao_vars_uma_pv_error(p):
    "secao_declaracao_vars : VAR declaracao_vars error"
    erro_sintatico(p, 3, "Esperado ';'")

def p_secao_declaracao_vars_varias_error(p):
    "secao_declaracao_vars : error declaracao_vars ';' secao_declaracao_vars"
    erro_sintatico(p, 1, "Necessário VAR para declarar váriaveis")

def p_secao_declaracao_vars_varias_pv_error(p):
    "secao_declaracao_vars : VAR declaracao_vars error secao_declaracao_vars"
    erro_sintatico(p, 3, "Esperado ';'")

def p_declaracao_vars_tipo_error(p):
    "declaracao_vars : lista_ids ':' error"
    erro_sintatico(p, 3, "Erro no tipo da varíavel")

def p_declaracao_vars_dp_error(p):
    "declaracao_vars : lista_ids error tipo"
    erro_sintatico(p, 2, "Esperado ':'")

def p_id_um_error(p):
    "ids : error"
    erro_sintatico(p, 1, "Identificador inválido")

def p_id_varios_error(p):
    "ids : error ',' ids"
    erro_sintatico(p, 1, "Identificador inválido")

# def p_id_varios_v_error(p):
#     "ids : ID error ids"
#     erro_sintatico(p, 2, "Esperado ','")
    
# def p_logico(p):
#     "logico : error"
#     erro_sintatico(p, 1, "Valores lógicos inválidos")

# def p_comando_composto_begin_error(p):
#     "comando_composto : error lista_comandos END"
#     erro_sintatico(p, 1, "Esperado BEGIN no ínicio do bloco")

# def p_comando_composto_end_error(p):
#     "comando_composto : BEGIN lista_comandos error"
#     erro_sintatico(p, 3, "Esperado END no fim do bloco")

# def p_lista_comandos_varios_error(p):
#     "lista_comandos : comando error lista_comandos"
#     erro_sintatico(p, 2, "Esperado ';'")
    
# def p_atribuicao_id_error(p):
#     "atribuicao : error ATRIB expr"
#     erro_sintatico(p, 1, "Identificador inválido")

# def p_atribuicao_atrib_error(p):
#     "atribuicao : ID error expr"
#     erro_sintatico(p, 2, "Esperado '='")

# def p_condicional_if_error(p):
#     '''condicional : error expr THEN comando %prec IFX
#                    | error expr THEN comando ELSE comando'''
#     erro_sintatico(p, 1, "Esperado IF")

# def p_condicional_then_error(p):
#     '''condicional : IF expr error comando %prec IFX
#                    | IF expr error comando ELSE comando'''
#     erro_sintatico(p, 3, "Esperado THEN")

# def p_condicional_else_error(p):
#     '''condicional : IF expr THEN comando error comando'''
#     erro_sintatico(p, 5, "Esperado ELSE")

# def p_repeticao_while_error(p):
#     "repeticao : error expr DO comando "
#     erro_sintatico(p, 1, "Esperado WHILE")

# def p_repeticao_do_error(p):
#     "repeticao : WHILE expr DO comando "
#     erro_sintatico(p, 3, "Esperado DO")

# def p_leitura_read_error(p):
#     "leitura : error '(' lista_ids ')' "
#     erro_sintatico(p, 1, "Esperado READ")

# def p_leitura_l_error(p):
#     "leitura : READ error lista_ids ')' "
#     erro_sintatico(p, 2, "Esperado '()'")

# def p_leitura_r_error(p):
#     "leitura : READ '(' lista_ids error "
#     erro_sintatico(p, 4, "Esperado ')'")

# def p_escrita_write_error(p):
#     "escrita : error '(' lista_expr ')'"
#     erro_sintatico(p, 1, "Esperado WRITE")

# def p_escrita_l_error(p):
#     "escrita : WRITE error lista_expr ')'"
#     erro_sintatico(p, 2, "Esperado '('")

# def p_escrita_r_error(p):
#     "escrita : WRITE '(' lista_expr error"
#     erro_sintatico(p, 4, "Esperado )")

# def p_lista_expr_varias_error(p):
#     "expressao : expressao expr error"
#     erro_sintatico(p, 3, "Esperado ','")

# def p_relacao_error(p):
#     "relacao : error"
#     erro_sintatico(p, 1, "Operador relacional inválido")

# def p_operador_termo_error(p):
#     "operador_termo : error"
#     erro_sintatico(p, 1, "Operador inválido, esperado (+, -, or)")

# def p_operador_fator_error(p):
#     "operador_fator : error"
#     erro_sintatico(p, 1, "Operador inválido, esperado (*, div, and)")

# def p_fator_error(p):
#     "fator : error"
#     erro_sintatico(p, 1, "Fator inválido")
# =============================================================================================== #
# Erro sintático
def p_error(p):
    if p is None:
        print("ERRO SINTÁTICO: fim de arquivo inesperado (EOF)")
        return
    # print(f"ERRO SINTÁTICO na linha {p.lineno}: token inesperado {p.value!r}")

def erro_sintatico(producao, posicao, mensagem):
    if producao:
        col = calculate_column(producao[posicao])
        print(f"ERRO SINTÁTICO: {mensagem} na linha {producao.lineno(posicao)}, coluna {col}")
        parser.errok()
    else:
        print("ERRO SINTÁTICO: fim inesperado de arquivo (EOF)")

global parser
parser = yacc.yacc(start='programa')

# Instancia o parser
# def make_parser(start='programa'):
#     global parser
#     parser = yacc.yacc(start=start)
#     return parser