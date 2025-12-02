from __future__ import annotations
from typing import List
import ast_cldin2 as ast
from defs_cldin2 import Visitador, Simbolo, Categoria, Tipo, TIPO_REAL, TIPO_BOOL

class TabelaSimbolos:
    def __init__(self):
        self.tabela = {}
        self.deslocamento_atual: int = 0
    
    def instala(self, s: Simbolo) -> str|None:
        if s.nome in self.tabela:
            return f"Identificador '{s.nome}' já declarado"
        s.deslocamento = self.deslocamento_atual
        self.tabela[s.nome] = s
        self.deslocamento_atual += 1
        return None

    def busca(self, nome):
        return self.tabela.get(nome, None)
    
    @property
    def total_var_alocadas(self):
        return self.deslocalmento_atual


class VerificadorSemantico(Visitador):
    def __init__(self):
        self.ts = TabelaSimbolos()
        self.tem_erro = False
        self.condicional = False
        pass

    def visita_Programa(self, no: ast.Programa):
        self.visita(no.bloco_cmds)
        no.total_vars = self.ts.total_var_alocadas

    def visita_BlocoCmds(self, no: ast.BlocoCmds):
        for cmd in no.lista_cmds:
            self.visita(cmd)

    def visita_Declaracao(self, no: ast.Declaracao):
        if self.condicional:
            print(f"Erro: declaração dentro de condicional")
            self.tem_erro = True
            return
        if no.nome_tipo == 'real':
            tipo_var = TIPO_REAL
        else: 
            tipo_var = TIPO_BOOL
        
        s = Simbolo(nome=no.id.nome, cat=Categoria.VAR, tipo=tipo_var)
        msg_erro = self.ts.instala(s)
        if msg_erro:
            print(msg_erro)
            self.tem_erro = True
            return
        
        self.visita(no.id)

    def visita_Condicional(self, no: ast.Condicional):
        self.visita(no.condicao)
        if no.condicao.tipo is not TIPO_BOOL:
            print(f"Erro: condicional não é de tipo booleano")
            self.tem_erro = True
            return
        self.condicional = True
        self.visita(no.bloco_then)
        self.condicional = False
        if no.bloco_else is not None:
            self.condicional = True
            self.visita(no.bloco_else)
            self.condicional = False       

    def visita_Funcao(self, no: ast.Funcao):
        self.visita(no.argumento)

    def visita_Atribuicao(self, no: ast.Atribuicao):
        # visita lado esq e dir e verifica se é igual o tipo
        self.visita(no.esq)

    def visita_CalculoBinario(self, no: ast.CalculoBinario):
        self.imprime("(CalcBin ")
        self.visita(no.esq)
        self.imprime(f" {no.op} ")
        self.visita(no.dir)
        self.imprime(")")

    def visita_CalculoUnario(self, no: ast.CalculoUnario):
        self.imprime(f"(CalcUn {no.op} ")
        self.visita(no.calculo)
        self.imprime(")")

    def visita_CalcId(self, no: ast.CalcId):
        s = self.ts.busca(no.nome)
        if s is None:
            print(f"Variável não declarada")
            return
        no.simbolo = s 
        no.tipo = s.tipo

    def visita_CalcConstNum(self, no: ast.CalcConstNum):
        no.tipo = TIPO_REAL

    def visita_CalcConstBool(self, no: ast.CalcConstBool):
        no.tipo = TIPO_BOOL