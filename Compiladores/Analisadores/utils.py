from enum import Enum

# Cálculo de coluna
def calculate_column(token):
    line_start = token.lexer.lexdata.rfind('\n', 0, token.lexpos) + 1
    return token.lexpos - line_start + 1

def erro_semantico(token, mensagem):
    col = calculate_column(token)
    print(f"ERRO SEMÂNTICO: {mensagem} na linha {token.lineno}, coluna {col}")

class Tipagem(Enum):
    INT  = 0
    BOOL = 1
    PRGM = 2

def nome_do_tipo(t: Tipagem) -> str:
    if t is Tipagem.INT:  return 'integer'
    if t is Tipagem.BOOL: return 'boolean'
    if t is Tipagem.PRGM: return 'programa'

# Tabela de simbolos
# Nome | Tipo | Linha | Coluna | Valor | Escopo
class TabelaSimbolos:
    def __init__(self, reserved=None):
        self.tabela = {}
        self.reserved = reserved or {}

    def inserir(self, nome: str, tipo: Tipagem = None, linha: int = None, coluna: int = None, valor=None, escopo = 'global'):
        # Verifica se é palavra reservada
        if nome in self.reserved:
            print(f"ERRO SEMÂNTICO: '{nome}' é palavra reservada na (linha {linha}, coluna {coluna}).")
            return True
        # Verifica se a VAR já foi declarada
        elif nome in self.tabela:
            print(f"ERRO SEMÂNTICO: '{nome}' já declarado neste anteriormente (linha {linha}, coluna {coluna}).")
            return True
        # Verifica se o tipo é permitido
        elif (tipo is not None) and (not isinstance(tipo, Tipagem)):
            print(f"ERRO SEMÂNTICO: Tipo '{tipo}' inválido para '{nome}' na (linha {linha}, coluna {coluna}). "
                            f"Tipos válidos: {[t.name for t in Tipagem]}")
            return True
        # Insere símbolo na tabela
        else:
            # Mapeia o tipo Enum para string
            tipo_id = nome_do_tipo(tipo) if tipo is not None else None
            self.tabela[nome] = {
                "tipo": tipo_id,
                "linha": linha,
                "coluna": coluna,
                "valor": valor,
                "escopo": escopo
            }
            return False

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

        # Salva um arquivo .txt
        with open("tabela_simbolos.txt", "w", encoding="utf-8") as arquivo:
            arquivo.writelines(conteudo)

        print("Tabela de símbolos salva em 'tabela_simbolos.txt'.")