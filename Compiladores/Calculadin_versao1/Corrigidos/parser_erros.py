# parser.py
import sys
import ply.yacc as yacc
from lexer import tokens, make_lexer

# Classe da tabela de símbolos
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
# Parser global (para o p_error consumir tokens)
parser = None

# Tratamento de erro semântico
def erro_semantico(msg, lineno=None):
    global tem_erro
    tem_erro = True
    if lineno is None:
        print(f"ERRO SEMÂNTICO: {msg}")
    else:
        print(f"ERRO SEMÂNTICO na linha {lineno}: {msg}")

# Regras gramaticais corretas
# def p_programa(p):
#     """programa : INICIAR CALCULADIN ':' lista_comandos FINALIZAR CALCULADIN PONTO"""
#     p[0] = None
def p_programa(p):
    """programa : cabecalho lista_comandos rodape"""
    p[0] = None

def p_cabecalho(p):
    """cabecalho : INICIAR CALCULADIN ':'"""
    p[0] = None

def p_rodape_ok(p):
    """rodape : FINALIZAR CALCULADIN PONTO"""
    p[0] = None

def p_lista_comandos(p):
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

# Regras de ERRO
# Cabeçalho (iniciar calculadin :)
def p_cabecalho_iniciar_erro(p):
    "cabecalho : error CALCULADIN ':'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(1)}: esperava 'iniciar'")
    global tem_erro; tem_erro = True
    parser.errok()

def p_cabecalho_calculadin_erro(p):
    "cabecalho : INICIAR error ':'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(2)}: esperava 'calculadin' após 'iniciar'")
    global tem_erro; tem_erro = True
    parser.errok()

def p_cabecalho_sem_dois_pts(p):
    "cabecalho : INICIAR CALCULADIN error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: esperava ':' após 'iniciar calculadin'")
    global tem_erro; tem_erro = True
    parser.errok()

# Rodapé (finalizar calculadin .) 
def p_rodape_finalizar_erro(p):
    "rodape : error CALCULADIN PONTO"
    print(f"ERRO SINTÁTICO na linha {p.lineno(1)}: esperava 'finalizar' antes do encerramento do programa")
    global tem_erro; tem_erro = True
    parser.errok()

def p_rodape_calculadin_erro(p):
    "rodape : FINALIZAR error PONTO"
    print(f"ERRO SINTÁTICO na linha {p.lineno(2)}: esperava 'calculadin' após 'finalizar'")
    global tem_erro; tem_erro = True
    parser.errok()

def p_rodape_sem_ponto_final(p):
    "rodape : FINALIZAR CALCULADIN error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: esperava '.' para finalizar o programa")
    global tem_erro; tem_erro = True
    parser.errok()

# Lista de comandos / delimitadores
def p_lista_comandos_err_cmd(p):
    "lista_comandos : lista_comandos error ';'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(2)}: comando inválido (descartando até ';')")
    global tem_erro; tem_erro = True
    parser.errok()

def p_lista_comandos_falta_pt_virg(p):
    "lista_comandos : lista_comandos comando error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: faltou ';' após comando")
    global tem_erro; tem_erro = True
    parser.errok()

def p_lista_comandos_comando_vazio(p):
    "lista_comandos : lista_comandos ';'"
    print(f"ERRO SINTÁTICO: comando vazio antes de ';'")
    global tem_erro; tem_erro = True
    # segue sem errok(); a redução já consome o ';'

# Chamadas de função
def p_chamada_funcao_input_arg_erro(p):
    "chamada_funcao : INPUT '(' error ')'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: input() espera um identificador")
    global tem_erro; tem_erro = True
    parser.errok()

def p_chamada_funcao_output_arg_erro(p):
    "chamada_funcao : OUTPUT '(' error ')'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: output() espera um identificador")
    global tem_erro; tem_erro = True
    parser.errok()

def p_chamada_funcao_input_falta_fecha(p):
    "chamada_funcao : INPUT '(' ID error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(4)}: faltou ')' em input()")
    global tem_erro; tem_erro = True
    parser.errok()

def p_chamada_funcao_output_falta_fecha(p):
    "chamada_funcao : OUTPUT '(' ID error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(4)}: faltou ')' em output()")
    global tem_erro; tem_erro = True
    parser.errok()

# Atribuição
def p_atribuicao_ld_erro(p):
    "atribuicao : ID '=' error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: expressão inválida à direita de '='")
    global tem_erro; tem_erro = True
    parser.errok()

# Fatores com parênteses
def p_fator_parens_expr_erro(p):
    "fator : '(' error ')'"
    print(f"ERRO SINTÁTICO na linha {p.lineno(2)}: expressão inválida entre parênteses")
    global tem_erro; tem_erro = True
    parser.errok()

def p_fator_parens_falta_fecha(p):
    "fator : '(' expr error"
    print(f"ERRO SINTÁTICO na linha {p.lineno(3)}: faltou ')' no fator")
    global tem_erro; tem_erro = True
    parser.errok()

# Função de erro geral
def p_error(tok):
    global tem_erro
    tem_erro = True
    if tok is None:
        print("ERRO SINTÁTICO: fim de arquivo inesperado (EOF)")
        return
    print(f"ERRO SINTÁTICO na linha {tok.lineno}: token inesperado ({tok.value!r})")

# Instancia o parser
def make_parser(start='programa'):
    global parser
    parser = yacc.yacc(start=start)
    return parser

# Para testar o parser sozinho: python3 parser.py < exemplo.calc
if __name__ == "__main__":
    data = sys.stdin.read()
    parser = make_parser()
    parser.parse(data, lexer=make_lexer())
    if not tem_erro:
        print('Parabéns, seu programa está correto!')
