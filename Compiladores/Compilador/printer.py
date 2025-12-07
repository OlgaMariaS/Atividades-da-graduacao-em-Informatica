from __future__ import annotations
import AST as ast
from utils import Visitador
import sys

class ImpressoraAST(Visitador):
    def __init__(self, saida=sys.stdout):
        self.saida = saida

    def imprime(self, texto: str):
        self.saida.write(texto)

    # PROGRAMA E BLOCO
    def visita_Programa(self, no: ast.Programa):
        self.imprime(f"(PROGRAM {no.nome} ")
        self.visita(no.bloco)
        self.imprime(")\n")

    def visita_Bloco(self, no: ast.Bloco):
        self.imprime("(BLOCO ")
        self.imprime("(DECLS")
        for decl in no.declaracoes:
            self.imprime(" ")
            self.visita(decl)
        self.imprime(") ")
        self.visita(no.comando)
        self.imprime(")")

    # DECLARAÇÕES
    def visita_Declaracao(self, no: ast.Declaracao):
        self.imprime(f"(DECL {no.tipo} (")
        for nome in no.nomes:
            self.imprime(f" {nome}")
        self.imprime(" ))")

    # COMANDOS
    def visita_BlocoCmds(self, no: ast.BlocoCmds):
        self.imprime("(BEGIN")
        for cmd in no.lista_cmds:
            self.imprime(" ")
            self.visita(cmd)
        self.imprime(" END)")

    def visita_Atribuicao(self, no: ast.Atribuicao):
        self.imprime("(ATRIB ")
        self.visita(no.id)
        self.imprime(" ")
        self.visita(no.calculo)
        self.imprime(")")

    def visita_Condicional(self, no: ast.Condicional):
        self.imprime("(IF ")
        self.visita(no.condicao)
        self.imprime(" THEN ")
        self.visita(no.bloco_then)
        if no.bloco_else:
            self.imprime(" ELSE ")
            self.visita(no.bloco_else)
        self.imprime(")")

    def visita_Repeticao(self, no: ast.Repeticao):
        self.imprime("(WHILE ")
        self.visita(no.condicao)
        self.imprime(" DO ")
        self.visita(no.corpo)
        self.imprime(")")

    def visita_Leitura(self, no: ast.Leitura):
        self.imprime("(READ")
        for id_ in no.ids:
            self.imprime(" ")
            self.visita(id_)
        self.imprime(")")

    def visita_Escrita(self, no: ast.Escrita):
        self.imprime("(WRITE")
        for expr in no.exprs:
            self.imprime(" ")
            self.visita(expr)
        self.imprime(")")

    # EXPRESSÕES
    def visita_CalculoBinario(self, no: ast.CalculoBinario):
        self.imprime("(BIN ")
        self.visita(no.esq)
        self.imprime(f" {no.op} ")
        self.visita(no.dir)
        self.imprime(")")

    def visita_CalculoUnario(self, no: ast.CalculoUnario):
        self.imprime(f"(UN {no.op} ")
        self.visita(no.calculo)
        self.imprime(")")

    def visita_CalcId(self, no: ast.CalcId):
        self.imprime(f"(ID {no.nome})")

    def visita_CalcConstNum(self, no: ast.CalcConstNum):
        self.imprime(f"(NUM {no.valor})")

    def visita_CalcConstBool(self, no: ast.CalcConstBool):
        self.imprime(f"(BOOL {no.valor})")
