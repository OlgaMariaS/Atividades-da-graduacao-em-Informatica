# from lexico import reserved 
from enum   import Enum
import lexico

# Cálculo de coluna
def calculate_column(token):
    line_start = token.lexer.lexdata.rfind('\n', 0, token.lexpos) + 1
    return token.lexpos - line_start + 1

class Tipo(Enum):
    INT  = 0
    BOOL = 1

def nomeTipo(t: Tipo) -> str:
    if t is Tipo.INT:  return 'int'
    if t is Tipo.BOOL: return 'bool'
    return "erro"

def erro_semantico(token, mensagem):
    col = calculate_column(token)
    print(f"ERRO SEMÂNTICO: {mensagem} na linha {token.lineno}, coluna {col}")

# Tabela de simbolos
# Nome | Tipo | Endereço (L,C) | Valor

#  -- O identificador do programa deve ser instalado na tabela de símbolos como sendo da categoria “programa”
class TabelaSimbolos:
    def __init__(self):
        self.tabela = {}

    def inserir(self, nome, tipo=None, linha=None, coluna=None, valor=None):
        # Verifica se é palavra reservada
        if nome in lexico.reserved:
            raise Exception(f"ERRO SEMÂNTICO: '{nome}' é palavra reservada na (linha {linha}, coluna {coluna}).") # checar se pode parar com exception
        # Verifica se a VAR já foi declarada
        elif nome in self.tabela:
            raise Exception(f"Erro semântico: '{nome}' já declarado neste anteriormente (linha {linha}, coluna {coluna}).")
        else:
            # Insere símbolo na tabela
            self.tabela[nome] = {
                "tipo": tipo,
                "linha": linha,
                "coluna": coluna,
                "valor": valor
            }

    # Busca símbolo na tabela
    def buscar(self, nome):
        return self.tabela.get(nome, None)
    
    # Exibe a tabela
    def exibir_tabela(self):
        conteudo = []
        conteudo.append("======= TABELA DE SÍMBOLOS =======\n")

        if not self.tabela:
            conteudo.append("Tabela vazia.\n")
        else:
            for nome, info in self.tabela.items():
                conteudo.append(f"\nID: {nome}")
                conteudo.append(f"\n  -Tipo   : {info['tipo']}")
                conteudo.append(f"\n  -Linha  : {info['linha']}")
                conteudo.append(f"\n  -Coluna : {info['coluna']}")
                conteudo.append(f"\n  -Valor  : {info['valor']}\n")

        conteudo.append("==================================\n")

        # Salva no arquivo .txt
        with open("tabela_simbolos.txt", "w", encoding="utf-8") as arquivo:
            arquivo.writelines(conteudo)

        print("Tabela de símbolos salva em 'tabela_simbolos.txt'.")

# reserved = ["program", "begin", "end"]

# tabela = TabelaSimbolos()
# tabela.inserir("x", tipo="inteiro", linha=1, coluna=4, valor=10)
# tabela.inserir("y", tipo="real", linha=2, coluna=8)
# tabela.exibir_tabela()
