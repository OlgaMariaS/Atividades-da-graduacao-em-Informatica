import ply.lex as lex
from utils import calculate_column

# dictionary of reserved words
reserved = {
    'program':  'PROGRAM',
    'var':      'VAR',
    'end':      'END',
    'read':     'READ',
    'write':    'WRITE',
    'begin':    'BEGIN',
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

literals = [':','=',';','(',')','<', '>','*','+','-',',','.']

tokens = (
   'NUM',
   'ID',
   'DIF',
   'LESS',
   'GREATER',
   'ATRIB',
) + tuple(reserved.values())

t_DIF     = r'<>'
t_LESS    = r'<='
t_GREATER = r'>='
t_ATRIB   = r':='

# NUM: Sequency of one or more digits
def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

# ID: start with a letter and optionally follows with a letter/digit/underscore
def t_ID(t):
    r'[A-Za-z][A-Za-z0-9_]*'
    t.type = reserved.get(t.value, 'ID') # Check if the word is reserved
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    t.lexer.line_start = t.lexpos + len(t.value) # update line_start to count columns

# # Count columns in line
# def calculate_column(t, lexico):
#     line_start = getattr(lexico, 'line_start', 0)
#     return t.lexpos - line_start + 1

# Ignore spaces and tabulations
t_ignore = ' \t'

# Report error and ignore invalid simbol
def t_error(t):
    col = calculate_column(t)
    print(f"ERRO LÉXICO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}, coluna {col}")
    t.lexer.skip(1)

lexer = lex.lex()