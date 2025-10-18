import ply.lex as lex

# Dicionário de palavras reservadas mapeadas para o tipo do token
p_reservadas = {
    'program': 'PROGRAM',
    'end': 'END',
}

# Literais de 1 caractere (retornam como tokens com type == value)
literals = '=+;.'

# Tupla de tokens válidos (poderia ser lista tb)
tokens = (
   'NUM',
   'ID',
) + tuple(p_reservadas.values())

# Expressões regulares para tokens com ações
# NUMERO: sequência de um ou mais dígitos
def t_NUM(t):
    r'\d+'
    # converte a string casada para um int
    t.value = int(t.value)
    return t

# ID: começa com letra, segue com letras/dígitos/underscore
def t_ID(t):
    r'[A-Za-z][A-Za-z0-9_]*'
    # Verifica se é palavra reservada
    t.type = p_reservadas.get(t.value, 'ID')  # se t.value estiver em 'p_reservadas', retorna o valor associado; senão retorna ID
    return t

# Nova linha
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)  # atualiza lineno sempre que encontrar uma quebra de linha
    # t.lexpos é a posição absoluta, em caracteres, do 1o \n da sequência em relação ao início do arquivo
    # len(t.value) é o tamanho da sequência de quebras de linha
    # t.lexpos + len(t.value) corresponde a posição do 1o caractere depois da sequência de \n, i.e., da próxima linha
    t.lexer.line_start = t.lexpos + len(t.value) # atualiza line_start para contar colunas

# Conta colunas de uma linha
def calcula_coluna(t, lexico):
    # coluna começando em 1
    line_start = getattr(lexico, 'line_start', 0) # getattr(obj, attr, default) é função nativa do Python
    # soma 1 para o valor de coluna começar em 1
    return t.lexpos - line_start + 1

# Ignora espaços e tabulaçãoes
t_ignore = ' \t'

# Reporta erros e ignora o símbolo inválido
def t_error(t):
    # calcula a coluna do erro
    col = calcula_coluna(t, t.lexer)
    print(f"ERRO: Símbolo ilegal {t.value[0]!r} na linha {t.lineno}, coluna {col}")
    t.lexer.skip(1) # descarta o caractere ilegal

lexico = lex.lex()