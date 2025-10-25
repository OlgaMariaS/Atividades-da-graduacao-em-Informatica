import ply.yacc as yacc
from enum   import Enum
from lexico import tokens
from utils  import calculate_column, TabelaSimbolos, erro_semantico

# instância global da classe TabelaSimbolos
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
    # if len(p) == 2:
    #     p[0] = p[1] + p[3]
    # elif len(p) == 2:
    #     p[0] = p[1] - p[3]

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
    p[0] = []

def p_fator_varios(p):
    "lista_fatores : lista_fatores operador_fator fator"

def p_operador_fator(p):
    '''operador_fator : '*'
                      | DIV
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
    "fator : NEG fator %prec UMINUS"

# =============================================================================================== #
# Produções para sinalização de erros sintáticos  
def p_programa_bloco_error(p):
    "programa : programa_begin error DOT"
    erro_sintatico(p, 2, "Erro no bloco de código")
    # print(f"ERRO SINTÁTICO: Falta bloco de código na linha {p.lineno(2)}")
    # parser.errok()

def p_programa_begin_error(p):
    "programa_begin : error ID ';' "
    erro_sintatico(p, 1, "Falta program")
    # print(f"ERRO SINTÁTICO: Falta program na linha {p.lineno(1)}")
    # parser.errok()

def p_programa_id_error(p):
    "programa_begin : PROGRAM error ';' " 
    erro_sintatico(p, 2, "Nome do programa não encontrado")
    # print(f"ERRO SINTÁTICO: Nome do programa não encontrado na linha {p[2].lineno}")
    # parser.errok()
    
def p_programa_pv_error(p):
    "programa_begin : PROGRAM ID error" 
    erro_sintatico(p, 3, "Esperado ';'")
    # print(f"ERRO SINTÁTICO: Esperado ';' na linha {p[3].lineno}")
    # parser.errok()

def p_programa_dot_error(p):
    "programa : programa_begin bloco error"
    erro_sintatico(p, 3, "Esperado '.'")
    # print(f"ERRO SINTÁTICO: Esperado '.' para finalizar o programa na linha {p.lineno(3)}")
    # parser.errok()
# =============================================================================================== #
# Erro sintático
def p_error(p):
    if p is None:
        print("ERRO SINTÁTICO: fim de arquivo inesperado (EOF)")
        return
    # print(f"ERRO SINTÁTICO na linha {p.lineno}: token inesperado ({p.value!r})")

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