# from lexico import reserved 

# Cálculo de coluna
def calculate_column(token):
    line_start = token.lexer.lexdata.rfind('\n', 0, token.lexpos) + 1
    return token.lexpos - line_start + 1

# class Tipo(Enum):
#     INT  = 0
#     BOOL = 1

# Funções de erro semântico
# def nomeTipo(t: Tipo) -> str:
#     if t is Tipo.INT:  return 'int'
#     if t is Tipo.BOOL: return 'bool'
#     return "erro"

mensagens_erros = {
    1: 'ERRO SEMÂNTICO',
    2: 'Bloco não fechado',
}

# Tabela de simbolos
# Nome dos identificadores | Tipo | Endereço (L,C) | Escopo | Valor

#  -- O identificador do programa deve ser instalado na tabela de símbolos como sendo da categoria “programa”

# criar um dict ou list com mensagem de erro, e então passar a função erro_semantico e só passar o indice do erro
    #  ex: 1: identificador não declarado

def erro_semantico(token, mensagem):
    col = calculate_column(token)
    print(f"ERRO SEMÂNTICO: {mensagem} na linha {token.lineno}, coluna {col}")

class TabelaSimbolos:
    def __init__(self):
        # Pilha de escopos (lista de dicionários)
        self.escopos = [{}]

    # Insere novo símbolo no escopo atual
    def inserir(self, nome, tipo, linha, valor=None):
        escopo_atual = self.escopos[-1]

        # Verifica se é palavra reservada
        if nome in reserved:
            raise Exception(f"ERRO SEMÂNTICO: '{nome}' é palavra reservada (linha {linha}).")

        # Verifica se já foi declarado no mesmo escopo
        if nome in escopo_atual:
            raise Exception(f"Erro semântico: '{nome}' já declarado neste escopo (linha {linha}).")

        # Insere símbolo
        escopo_atual[nome] = {
            "tipo": tipo,
            "linha": linha,
            "valor": valor
        }

    # Busca símbolo do escopo atual ou anteriores
    def buscar(self, nome):
        for escopo in reversed(self.escopos):
            if nome in escopo:
                return escopo[nome]
        return None  # Não encontrado

    # Cria novo escopo
    def novo_escopo(self):
        self.escopos.append({})

    # Sai do escopo atual
    def sair_escopo(self):
        if len(self.escopos) > 1:
            self.escopos.pop()
        else:
            raise Exception("Erro interno: tentativa de remover escopo global.")

    # Exibe a tabela (debug/visualização)
    def exiber_tabela(self):
        print("===== TABELA DE SÍMBOLOS =====")
        for i, escopo in enumerate(self.escopos):
            print(f"\nEscopo {i}:")
            for nome, info in escopo.items():
                print(f"  {nome}: {info}")
        print("===============================")