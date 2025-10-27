import ply.lex as lex
import sys
from utils import calculate_column

# Sinalizador de erros
existe_erro = False

# dictionary of reserved words
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

# Ignore spaces and tabulations
t_ignore = ' \t'

# Report error and ignore invalid simbol
def t_error(t):
    col = calculate_column(t)
    global existe_erro
    existe_erro = True
    print(f"ERRO LÉXICO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}, coluna {col}")
    
    t.lexer.skip(1)

# Instancia o lexer
def make_lexer():
    return lex.lex()
    
# Testar somente léxico
if __name__ == '__lexico__':
    data = sys.stdin.read()
    lexer = make_lexer()
    lexer.input(data)
    for tok in lexer:
        print(f'<{tok.type}, {tok.value!r}> na linha: {tok.lineno}')