import ply.lex as lex

p_reservadas = {
    'iniciar': 'INI',
    'calculadin': 'CALC',
    'input': 'INPUT',
    'output': 'OUTPUT',
    'finalizar': 'FIM',
}

literals = ['=', '+', '-', '*', '/', '(', ')', ':', ';']

# Tokens
tokens = (
   'ID',
   'NUM',
   'PONTO'
) + tuple(p_reservadas.values())

t_PONTO     = r'\.'

# Tokens com ações:
# NUMERO
def t_NUM(t):
    r'\d+(?:\.\d+)?'
    t.value = float(t.value)
    return t

# ID
def t_ID(t):
    r'[a-z][a-z0-9]*'
    t.type = p_reservadas.get(t.value, 'ID')
    return t

# Nova linha
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)  
    t.lexer.line_start = t.lexpos + len(t.value)

# Comentários de linha (// até o fim da linha)
def t_COMMENT(t):
    r'//[^\n]*'
    pass

# Conta colunas de uma linha
def calcula_coluna(t, lexico):
    line_start = getattr(lexico, 'line_start', 0)
    return t.lexpos - line_start + 1

# Ignora espaços, tabulaçãoes
t_ignore = ' \t'

# Reporta erros e ignora o símbolo inválido
def t_error(t):
    col = calcula_coluna(t, t.lexer)
    print(f"ERRO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}, coluna {col}")
    t.lexer.skip(1)

lexer = lex.lex()
