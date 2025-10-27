import sys
import ply.yacc as yacc
from lexico import tokens, reserved, make_lexer
from utils  import calculate_column, TabelaSimbolos, Tipagem, nome_do_tipo, erro_semantico

# instância TabelaSimbolos
tabela_simbolos = TabelaSimbolos(reserved)
# Sinalizador de erros
existe_erro = False
parser = None

# Regras de produção da gramática: 
precedence = (
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    ('left', 'OR'),
    ('left', '+', '-'),
    ('left', '*', 'DIV', 'AND'),
    ('right', 'UMINUS'),
    ('nonassoc', 'LOWEST'),
)

def p_programa(p):
    "programa : programa_begin bloco DOT"
    p[0] = None

def p_programa_begin(p):
    "programa_begin : PROGRAM ID ';'"
    simbolo = p[2]
    col = calculate_column(p.slice[2])
    tabela_simbolos.inserir(simbolo, Tipagem.PRGM, p.lineno(2), col)
    p[0] = None 

def p_bloco(p):
    '''bloco : secao_declaracao_vars comando_composto
             | comando_composto'''
    p[0] = None

def p_secao_declaracao_vars_uma(p):
    "secao_declaracao_vars : VAR declaracao_vars ';'"
    p[0] = None

def p_secao_declaracao_vars_varias(p):
    "secao_declaracao_vars : VAR declaracao_vars ';' secao_declaracao_vars"
    p[0] = None

def p_declaracao_vars(p):
    "declaracao_vars : lista_ids ':' tipo"
    tipo = p[3]
    global existe_erro
    for id_token in p[1]:
        col = calculate_column(id_token)
        existe_erro = tabela_simbolos.inserir(id_token.value, tipo, id_token.lineno, col)

def p_id_um(p):
    "lista_ids : ID"
    p[0] = [p.slice[1]]

def p_id_varios(p):
    "lista_ids : ID ',' lista_ids"
    p[0] = [p.slice[1]] + p[3]

def p_tipo (p):
    '''tipo : BOOL 
            | INT'''
    if p[1] == 'integer':
        p[0] = Tipagem.INT
    else:
        p[0] = Tipagem.BOOL

def p_logico(p):
    '''logico : TRUE 
              | FALSE'''
    p[0] = None

def p_comando_composto(p):
    "comando_composto : BEGIN lista_comandos END"
    global existe_erro

    if p[1] != 'begin':
        existe_erro = True
        erro_semantico(p.slice[1], "Deve existe um bloco BEGIN...END")
    else:
        p[0] = p[2]

def p_lista_comandos_um(p):
    "lista_comandos : comando %prec LOWEST" # menor precedencia
    p[0] = p[1]

def p_lista_comandos_varios(p):
    "lista_comandos : comando ';' lista_comandos"
    p[0] = p[1]

def p_comando (p):
    '''comando : atribuicao
               | condicional
               | repeticao
               | leitura
               | escrita
               | comando_composto'''
    p[0] = p[1]
    
def p_atribuicao(p):
    "atribuicao : ID ATRIB expr"
    global existe_erro
    id_info = tabela_simbolos.buscar(p[1])

    if id_info is None:
        existe_erro = True
        erro_semantico(p.slice[1], f"Identificador '{p[1]}' não declarado anteriormente")
    else:
        tipo_var = id_info["tipo"]
        tipo_expr = nome_do_tipo(p[3])
        if tipo_var != tipo_expr:
            existe_erro = True
            erro_semantico(p.slice[1], f"Tipos incompatíveis: variável '{p[1]}' é {tipo_var}, mas expressão é {tipo_expr}")
        else:
            p[0] = p[1]

def p_condicional(p):
    '''condicional : IF expr THEN comando %prec IFX
                   | IF expr THEN comando ELSE comando'''
    global existe_erro
    tipo_expr = p[2]

    if tipo_expr is None:
        existe_erro = True
        erro_semantico(p.slice[1], "Expressão condicional inválida")
    elif tipo_expr != Tipagem.BOOL:
        existe_erro = True
        erro_semantico(p.slice[1], "A condição do IF deve resultar em tipo lógico")
    else:
        p[0] = p[1]

def p_repeticao(p):
    "repeticao : WHILE expr DO comando"
    global existe_erro
    tipo_expr = p[2]

    if tipo_expr is None:
        existe_erro = True
        erro_semantico(p.slice[1], "Expressão condicional inválida")
    elif tipo_expr != Tipagem.BOOL:
        existe_erro = True
        erro_semantico(p.slice[1], "A condição do WHILE deve ser do tipo lógico")
    else:
        p[0] = p[1]

def p_leitura(p):
    "leitura : READ '(' lista_ids ')'"
    global existe_erro

    for id_token in p[3]:
        simbolo = tabela_simbolos.buscar(id_token.value)
        if simbolo is None:
            existe_erro = True
            erro_semantico(id_token, f"Identificador '{id_token.value}' não declarado para leitura")
        else:
            p[0] = p[1]

def p_escrita(p):
    "escrita : WRITE '(' lista_expr ')' "
    global existe_erro

    for expr_tipo in p[3]:
        if expr_tipo is None:
            existe_erro = True
            erro_semantico(p.slice[1], "Expressão inválida na escrita")
        else:
            p[0] = p[1]

# retorna um lista de expressões
def p_lista_expr_uma(p):
    "lista_expr : expr %prec LOWEST"
    p[0] = [p[1]]

def p_lista_expr_varias(p):
    "lista_expr : expr ',' lista_expr"
    p[0] = [p[1]] + p[3]

def p_expr(p):
    '''expr : expr_simples
            | expr_simples relacao expr_simples'''
    global existe_erro

    if len(p) == 2:
        p[0] = p[1]
    else:
        tipo_esq = p[1]
        operador = p[2]
        tipo_dir = p[3]

        if tipo_esq is None or tipo_dir is None:
            p[0] = None
        elif operador in ['=', '<>']: # Igualdade/diferença as expressões devem ter tipos iguais
            if tipo_esq != tipo_dir:
                existe_erro = True
                erro_semantico(p.slice[2], f"Comparação '{operador}' requer operandos do mesmo tipo")
            p[0] = Tipagem.BOOL
        else: # (<, >, <=, >=) 
            if tipo_esq != Tipagem.INT or tipo_dir != Tipagem.INT:
                existe_erro = True
                erro_semantico(p.slice[2], f"Operador relacional '{operador}' somente com inteiros")
            p[0] = Tipagem.BOOL

def p_relacao(p):
    '''relacao : '='
               | DIF
               | '<'
               | LESS
               | '>'
               | GREATER '''
    p[0] = p.slice[1]

def p_expr_simples(p):
    "expr_simples : termo lista_termos"
    p[0] = p[1]

def p_termo_vazio(p):
    "lista_termos : "
    p[0] = None

def p_termos_varios(p):
    "lista_termos : lista_termos operador_termo termo"
    global existe_erro
    tipo_esq = p[1]
    operador = p[2]
    tipo_dir = p[3]

    if tipo_esq is None or tipo_dir is None:
        p[0] = None
    if operador in ['+', '-']:
        if tipo_esq != Tipagem.INT or tipo_dir != Tipagem.INT:
            existe_erro = True
            erro_semantico(p.slice[2], f"Operação '{operador}' somente com inteiros")
        p[0] = Tipagem.INT
    elif operador == 'or':
        if tipo_esq != Tipagem.BOOL or tipo_dir != Tipagem.BOOL:
            existe_erro = True
            erro_semantico(p.slice[2], "Operador 'or' somente com booleanos")
        p[0] = Tipagem.BOOL

def p_operador_termo(p):
    '''operador_termo : '+'
                      | '-'
                      | OR '''
    p[0] = p.slice[1]
    
def p_termo(p):
    "termo : fator lista_fatores"
    p[0] = p[1]
    
def p_fator_vazio(p):
    "lista_fatores : "
    p[0] = None

def p_fator_varios(p):
    "lista_fatores : lista_fatores operador_fator fator"
    global existe_erro
    tipo_esq = p[1]
    operador = p[2]
    tipo_dir = p[3]

    if tipo_esq is None or tipo_dir is None:
        p[0] = None
        return
    if operador.value in ['*', 'DIV']:
        if tipo_esq != Tipagem.INT or tipo_dir != Tipagem.INT:
            existe_erro = True
            erro_semantico(operador, f"Operação '{operador}' somente com inteiros")
        p[0] = Tipagem.INT
    elif operador.value == 'and':
        if tipo_esq != Tipagem.BOOL or tipo_dir != Tipagem.BOOL:
            existe_erro = True
            erro_semantico(operador, "Operador 'and' somente com booleanos")
        p[0] = Tipagem.BOOL

def p_operador_fator(p):
    '''operador_fator : '*'
                      | DIV
                      | AND '''
    p[0] = p.slice[1]
         
def p_fator(p):
    '''fator : fator_id
             | fator_num
             | fator_log
             | fator_expr
             | fator_not
             | fator_neg '''
    p[0] = p[1]

def p_fator_num(p):
    "fator_num : NUM"
    p[0] = Tipagem.INT

def p_fator_log(p):
    "fator_log : logico"
    p[0] = Tipagem.BOOL

def p_fator_id(p):
    "fator_id : ID"
    simbolo = tabela_simbolos.buscar(p[1])
    if simbolo:
        p[0] = simbolo["tipo"]
    else:
        global existe_erro
        existe_erro = True
        erro_semantico(p.slice[1], f"Identificador '{p[1]}' não declarado")
        p[0] = None

def p_fator_expr(p):
    "fator_expr : '(' expr ')'"
    p[0] = p[2]

def p_fator_not(p):
    "fator_not : NOT fator"
    global existe_erro
    tipo = p[2]
    if tipo != Tipagem.BOOL:
        existe_erro = True
        erro_semantico(p.slice[1], "Operador 'not' somente com booleano")
    p[0] = Tipagem.BOOL

def p_fator_neg(p):
    "fator_neg : NEG fator %prec UMINUS"
    global existe_erro
    tipo = p[2]
    if tipo != Tipagem.INT:
        existe_erro = True
        erro_semantico(p.slice[1], "Operador de negação somente com inteiro")
    p[0] = Tipagem.INT
# ============================ Produções para sinalização de erros sintáticos =============================== #
def p_programa_begin_error(p):
    "programa_begin : error ID ';'"
    erro_sintatico(p, 1, "Falta program")

def p_programa_id_error(p):
    "programa_begin : PROGRAM error ';' " 
    erro_sintatico(p, 2, "Nome do programa não encontrado")
    
def p_programa_pv_error(p):
    "programa_begin : PROGRAM ID error"
    erro_sintatico(p, 3, "Esperado ';'")

def p_programa_dot_error(p):
    "programa : programa_begin bloco error"
    erro_sintatico(p, 3, "Esperado '.' no fim do arquivo")

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
    "lista_ids : error"
    erro_sintatico(p, 1, "Identificador inválido")

def p_id_varios_error(p):
    "lista_ids : error ',' lista_ids"
    erro_sintatico(p, 1, "Na declaração de variáveis")

# def p_comando_composto_begin_error(p):
#     "comando_composto : error lista_comandos END"
#     erro_sintatico(p, 1, "Esperado BEGIN no ínicio do bloco")

def p_comando_composto_end_error(p):
    "comando_composto : BEGIN lista_comandos error"
    erro_sintatico(p, 3, "Esperado END no fim do bloco")

def p_lista_comandos_varios_error(p):
    "lista_comandos : comando error lista_comandos"
    erro_sintatico(p, 2, "Esperado ';'")
    
def p_atribuicao_id_error(p): #  Alerta erro caso não seja declarado variável
    "atribuicao : error ATRIB expr"
    erro_sintatico(p, 1, "Identificador inválido")

def p_atribuicao_atrib_error(p):
    "atribuicao : ID error expr"
    erro_sintatico(p, 2, "Esperado ':=' para atribuição")

def p_condicional_if_error(p):
    '''condicional : error expr THEN comando %prec IFX
                   | error expr THEN comando ELSE comando'''
    erro_sintatico(p, 1, "Esperado IF")

def p_condicional_then_error(p):
    '''condicional : IF expr error comando %prec IFX
                   | IF expr error comando ELSE comando'''
    erro_sintatico(p, 3, "Esperado THEN")

def p_condicional_else_error(p):
    '''condicional : IF expr THEN comando error comando'''
    erro_sintatico(p, 5, "Esperado ELSE")

def p_repeticao_while_error(p):
    "repeticao : error expr DO comando "
    erro_sintatico(p, 1, "Esperado WHILE")

def p_repeticao_do_error(p):
    "repeticao : WHILE expr error comando "
    erro_sintatico(p, 3, "Esperado DO com o comando while")

# def p_leitura_read_error(p):
#     "leitura : error '(' lista_ids ')' "
#     erro_sintatico(p, 1, "Esperado READ")

def p_leitura_l_error(p):
    "leitura : READ error lista_ids ')' "
    erro_sintatico(p, 2, "Esperado '('")

def p_leitura_r_error(p):
    "leitura : READ '(' lista_ids error "
    erro_sintatico(p, 4, "Esperado ')'")

# def p_escrita_write_error(p):
#     "escrita : error '(' lista_expr ')'"
#     erro_sintatico(p, 1, "Esperado WRITE")

def p_escrita_l_error(p):
    "escrita : WRITE error lista_expr ')'"
    erro_sintatico(p, 2, "Esperado '('")

def p_escrita_r_error(p):
    "escrita : WRITE '(' lista_expr error"
    erro_sintatico(p, 4, "Esperado )")

def p_lista_expr_uma_error(p):
    "lista_expr : error"
    erro_sintatico(p, 1, "Problema nas expressões")

# def p_lista_expr_varias_error(p):
#     "lista_expr : expr error lista_expr"
#     erro_sintatico(p, 2, "Esperado ','")

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

def p_fator_expr_error(p):
    "fator_expr : '(' error ')'"
    erro_sintatico(p, 2, "Expressão inválida entre parênteses")

def p_fator_expr_r_error(p):
    "fator_expr : '(' expr error"
    erro_sintatico(p, 3, "Esperado um ')'")
# =============================================================================================== #
# Erro sintático
def p_error(p):
    global existe_erro
    existe_erro = True
    if p is None:
        print("ERRO SINTÁTICO: fim de arquivo inesperado (EOF)")
        return
    # print(f"ERRO SINTÁTICO na linha {p.lineno}: token inesperado {p.value!r}")

def erro_sintatico(producao, posicao, mensagem):
    if producao:
        col = calculate_column(producao[posicao])
        print(f"ERRO SINTÁTICO: {mensagem} na linha {producao.lineno(posicao)}, coluna {col}")
        parser.errok()
        global existe_erro
        existe_erro = True
    else:
        print("ERRO SINTÁTICO: fim inesperado de arquivo (EOF)")

# Instancia o parser
def make_parser(start='programa'):
    global parser
    global existe_erro 
    parser = yacc.yacc(start=start)
    return parser, existe_erro

# Testar somente parser
if __name__ == "__main__":
    data = sys.stdin.read()
    parser, existe_erro = parser.make_parser()
    parser.parse(data, lexer=make_lexer())
    if not existe_erro: 
        print('Programa executado com sucesso!')