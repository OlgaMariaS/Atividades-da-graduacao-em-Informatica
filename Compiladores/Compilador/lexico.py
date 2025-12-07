import ply.lex as lex

# Sinalizador de erros
existe_erro = False

# Dicionário de palavras reservadas
reserved = {
    'program':  'PROGRAM',
    'var':      'VAR',
    'read':     'READ',
    'write':    'WRITE',
    'begin':    'BEGIN',
    'end':      'END',
    'integer':  'INT',
    'boolean':  'BOOL',
    'false':    'FALSE',
    'true':     'TRUE',
    'while':    'WHILE',
    'do':       'DO',
    'if':       'IF',
    'then':     'THEN',
    'else':     'ELSE',
    'div':      'DIV',
    'and':      'AND',
    'or':       'OR',
    'not':      'NOT'
}

literals = ['(',')',':','=',';','<', '>','*','+','-',',']

tokens = (
   'NUM',
   'ID',
   'DIF',
   'LESS',
   'GREATER',
   'ATRIB',
   'NEG',
   'DOT',
) + tuple(reserved.values())

t_DIF     = r'<>'
t_LESS    = r'<='
t_GREATER = r'>='
t_ATRIB   = r':='
t_NEG     = r'-'
t_DOT    = r'\.'

# NUM: Sequencia de um ou mais digitos
def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

# ID: começa com uma letra e opcionalmente segue com letra/digito/underscore
def t_ID(t):
    r'[A-Za-z][A-Za-z0-9_]*'
    t.type = reserved.get(t.value, 'ID') # Checa se é palavra reservada
    return t


def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Ignora espaços e tabulações
t_ignore = ' \t'

# Reporta erro e ignora o simbolo inválido
def t_error(t):
    print(f"Erro léxico: Símbolo ilegal '{t.value[0]!r}' na linha {t.lexer.lineno}")
    t.lexer.tem_erro = True
    t.lexer.skip(1)

# Instancia o lexer
def make_lexer():
    lexer = lex.lex()
    lexer.tem_erro = False
    return lexer

        