# IMPORT 

# Cálculo de coluna
def calculate_column(token):
    line_start = token.lexer.lexdata.rfind('\n', 0, token.lexpos) + 1
    return token.lexpos - line_start + 1

# Tabela de simbolos
# Nome dos identificadores | Tipo | Endereço (L,C) | Escopo | Valor
# O identificador do programa deve ser instalado na tabela de símbolos como sendo da categoria “programa”

class TabelaSimbolos:
    def __init__(self):
        # Pilha de escopos (lista de dicionários)
        self.escopos = [{}]

    def inserir(self, nome, tipo, linha, valor=None):
        escopo_atual = self.escopos[-1]
        if nome in escopo_atual:
            raise Exception(f"Erro: variável '{nome}' já declarada neste escopo (linha {linha})")
        escopo_atual[nome] = {
            "tipo": tipo,
            "linha": linha,
            "valor": valor
        }

    def buscar(self, nome):
        for escopo in reversed(self.escopos):
            if nome in escopo:
                return escopo[nome]
        return None

    def novo_escopo(self):
        self.escopos.append({})

    def sair_escopo(self):
        self.escopos.pop()


# A variável à esquerda da atribuição deve estar declarada e visível no escopo atual.

# A expressão à direita deve ser semanticamente válida e possuir o mesmo tipo da variável à esquerda.