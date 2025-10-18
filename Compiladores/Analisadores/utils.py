# IMPORT 

# Cálculo de coluna
def calculate_column(token):
    line_start = token.lexer.lexdata.rfind('\n', 0, token.lexpos) + 1
    return token.lexpos - line_start + 1


# tabela de simbolos