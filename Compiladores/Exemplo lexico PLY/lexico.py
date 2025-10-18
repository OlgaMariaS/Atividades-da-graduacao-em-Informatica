import ply.lex as lex

# Dicionário de palavras reservadas mapeadas para o tipo do token
p_reservadas = {
    'program': 'PROGRAM',
}

# Tupla de tokens válidos (poderia ser lista tb)
tokens = (
   'PROGRAM',
   'NUM',
   'ID',
   'MAIS',
)

# Expressões regulares para tokens que não tem ações associadas
t_MAIS  = r'\+' # símbolo de adição

# Expressões regulares para tokens com ações
# NUMERO
def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

# ID: começa com letra, segue com letras/dígitos/underscore
def t_ID(t):
    r'[A-Za-z][A-Za-z0-9]*'
    # Reclassifica se for palavra reservada
    t.type = p_reservadas.get(t.value, 'ID')    # se t.value estiver em 'p_reservadas', retorne o valor; senão retorne ID
    return t

# Nova linha
def t_newline(t):
    r'\n+'
    # print(t.value)
    t.lexer.lineno += len(t.value)  # atualiza lineno sempre que encontrar uma quebra de linha
                                    # t.value vai conter a sequência de \n encontrada

# Ignora espaços e tabulaçãoes
t_ignore = ' \t'

# Detecta e ignora erros - não vai ocorre porque definimos OUTRO
def t_error(t):
    print("ERRO: Símbolo ilegal '%s' na linha '%d', posição '%d'" % (t.value[0], t.lexer.lineno, t.lexer.lexpos))
    t.lexer.skip(1)

lexico = lex.lex()

# if __name__ == "__main__":
#     data = '''
#     program meu_prog;
#         a = 1 + y*2
#         1x = 25
#     end.
#     '''
#     scanner.input(data)
#     while True:
#         tok = scanner.token()
#         if not tok:
#             break
#         print(tok)
#         # print(f'classe = {tok.type}, valor = {tok.value}, linha = {tok.lineno}, pos = {tok.lexpos}')