# parser.py
import sys
import ply.yacc as yacc
from lexer import tokens, make_lexer

class TabelaSimbolos:
    def __init__(self):
        self.tabela = {}

    # a função instala poderia associar qualquer outro atributo ao ID
    def instala(self, nome, tipo=None, endereco=None):
        if nome in self.tabela:
            return None
        self.tabela[nome] = {"tipo": tipo, "endereco": endereco}

    def busca(self, nome):
        return self.tabela.get(nome, None)

# tabela de símbolos
tab_simbolos =  TabelaSimbolos()
# flag global para sinalizar que tem erro
tem_erro = False

# Tratamento de erro semântico
def erro_semantico(msg, lineno=None):
    global tem_erro
    tem_erro = True
    if lineno is None:
        print(f"ERRO SEMÂNTICO: {msg}")
    else:
        print(f"ERRO SEMÂNTICO na linha {lineno}: {msg}")

# Regras gramaticais
def p_programa(p):
    """programa : INICIAR CALCULADIN ':' lista_comandos FINALIZAR CALCULADIN PONTO"""
    p[0] = None

def p_lista_comandos_rec(p):
    """lista_comandos : lista_comandos comando ';'"""
    p[0] = None

def p_lista_comandos_vazia(p):
    """lista_comandos : """
    p[0] = None

def p_comando(p):
    """comando : chamada_funcao
               | atribuicao"""
    p[0] = None

def p_chamada_funcao_input(p):
    """chamada_funcao : INPUT '(' ID ')'"""
    nome = p[3]
    # A primeira ocorrência do ID como argumento de input() corresponde à declaração
    tab_simbolos.instala(nome)
    p[0] = None

def p_chamada_funcao_output(p):
    """chamada_funcao : OUTPUT '(' ID ')'"""
    nome = p[3]
    # Só pode usar em output() se já foi declarado
    if tab_simbolos.busca(nome) is None:
        erro_semantico(f"variável '{nome}' usada em output() sem declaração prévia", p.lineno(3))
    p[0] = None

def p_atribuicao(p):
    """atribuicao : ID '=' expr"""
    nome = p[1]
    # A primeira ocorrência do ID no lado esquerdo da atribuição corresponde à declaração
    tab_simbolos.instala(nome)
    p[0] = None

def p_expr_binaria(p):
    """expr : expr '+' termo
            | expr '-' termo"""
    p[0] = None  

def p_expr_termo(p):
    """expr : termo"""
    p[0] = None

def p_termo_binario(p):
    """termo : termo '*' fator
             | termo '/' fator"""
    p[0] = None

def p_termo_fator(p):
    """termo : fator"""
    p[0] = None

def p_fator_parenteses(p):
    """fator : '(' expr ')'"""
    p[0] = None

def p_fator_numero(p):
    """fator : NUM"""
    p[0] = None

def p_fator_id(p):
    """fator : ID"""
    nome = p[1]
    # Identificadores usados no lado direito de expressões devem existir
    if tab_simbolos.busca(nome) is None:
        erro_semantico(f"variável '{nome}' usada em expressão sem declaração prévia", p.lineno(1))
    p[0] = None

# Erro sintático
def p_error(tok):
    global tem_erro
    tem_erro = True
    if tok is None:
        print("ERRO SINTÁTICO: fim de arquivo inesperado (EOF).")
    else:
        print(f"ERRO SINTÁTICO na linha {tok.lineno}: token inesperado ({tok.value!r})")

# Instancia o parser
def make_parser(start = 'programa'):
    return yacc.yacc(start=start)

# Para testar o parser sozinho: python3 parser.py < exemplo.calc
if __name__ == "__main__":
    data = sys.stdin.read()
    parser = make_parser()
    parser.parse(data, lexer=make_lexer())
    if not tem_erro: print('Parabéns, seu programa está correto!')
