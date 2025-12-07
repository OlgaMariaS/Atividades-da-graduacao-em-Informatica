from __future__ import annotations
from typing import List
import AST as ast
from utils import Visitador, Simbolo, Categoria, TIPO_INT, TIPO_BOOL, Tipo

class TabelaSimbolos:
    def __init__(self):
        self.tabela = {}
        self.deslocamento_atual = 0

    def instala(self, s: Simbolo):
        if s.nome in self.tabela:
            return f"Identificador '{s.nome}' já declarado."
        s.deslocamento = self.deslocamento_atual
        self.tabela[s.nome] = s
        self.deslocamento_atual += 1
        return None

    def busca(self, nome) -> Simbolo|None:
        return self.tabela.get(nome, None)

class AnalisadorSemantico(Visitador):
    def __init__(self):
        self.ts = TabelaSimbolos()
        self.erros: List[str] = []
        self.tem_erro = False
        # Controle de escopo: se True, declarações são proibidas
        self.dentro_condicional = False

    def _erro(self, msg):
        self.erros.append(msg)
        self.tem_erro = True

    def _nome(self, t: Tipo | None):
        if t is TIPO_INT: return "integer"
        if t is TIPO_BOOL: return "boolean"
        return "desconhecido"

    # Mapeamento dos tokens
    def _map_op(self, op: str):
        MAP = {
            "DIF": "<>",
            "<>": "<>",
            "LESS": "<=",
            "<=": "<=",
            "GREATER": ">=",
            ">=": ">=",
            "<": "<",
            ">": ">",
            "=": "=",
            "-": "-",
            "DIV": "div",
            "AND": "and",
            "OR": "or",
            "not": "not"
        }
        return MAP.get(op, op)
        
    def visita_Programa(self, prog: ast.Programa):
        sim = Simbolo(nome=prog.nome, cat=Categoria.PROG)
        erro = self.ts.instala(sim)
        if erro:
            self._erro(erro)

        self.visita(prog.bloco)
        prog.total_vars = self.ts.deslocamento_atual

    def visita_Bloco(self, bloco: ast.Bloco):
        for decl in bloco.declaracoes:
            self.visita(decl)
        self.visita(bloco.comando)

    def visita_Declaracao(self, decl: ast.Declaracao):
        if self.dentro_condicional:
            for n in decl.nomes:
                self._erro(f"Declarações não são permitidas dentro de if/while ('{n}').")
            return

        if decl.tipo == "integer":
            t = TIPO_INT
        elif decl.tipo == "boolean":
            t = TIPO_BOOL
        else:
            self._erro(f"Tipo desconhecido: {decl.tipo}")
            return

        for nome in decl.nomes:
            sym = Simbolo(nome=nome, cat=Categoria.VAR, tipo=t)
            erro = self.ts.instala(sym)
            if erro:
                self._erro(erro)

    def visita_BlocoCmds(self, bloco: ast.BlocoCmds):
        for cmd in bloco.lista_cmds:
            self.visita(cmd)

    def visita_Atribuicao(self, cmd: ast.Atribuicao):
        self.visita(cmd.id)
        self.visita(cmd.calculo)

        if cmd.id.tipo is None or cmd.calculo.tipo is None:
            return

        if cmd.id.tipo is not cmd.calculo.tipo:
            self._erro(
                f"Tipo incompatível na atribuição: '{cmd.id.nome}' "
                f"({self._nome(cmd.id.tipo)}) recebe {self._nome(cmd.calculo.tipo)}."
            )
            return

    def visita_Condicional(self, cmd: ast.Condicional):
        self.visita(cmd.condicao)

        if cmd.condicao.tipo is not TIPO_BOOL:
            self._erro("A condição do IF deve ser do tipo boolean.")

        # Ativa a flag que está em escopo de condicional
        self.dentro_condicional = True
        self.visita(cmd.bloco_then)
        if cmd.bloco_else:
            self.visita(cmd.bloco_else)
        self.dentro_condicional = False

    def visita_Repeticao(self, cmd: ast.Repeticao):
        self.visita(cmd.condicao)

        if cmd.condicao.tipo is not TIPO_BOOL:
            self._erro("A condição do WHILE deve ser do tipo boolean.")

        self.dentro_condicional = True
        self.visita(cmd.corpo)
        self.dentro_condicional = False

    def visita_Leitura(self, cmd: ast.Leitura):
        for idnode in cmd.ids:
            self.visita(idnode)
            if idnode.tipo is None:
                self._erro(f"Variável '{idnode.nome}' usada em READ não foi declarada.")

    def visita_Escrita(self, cmd: ast.Escrita):
        for expr in cmd.exprs:
            self.visita(expr)
            if expr.tipo is None:
                self._erro("Expressão inválida em WRITE.")

    def visita_CalculoBinario(self, c: ast.CalculoBinario):
        op = self._map_op(c.op)

        self.visita(c.esq)
        self.visita(c.dir)

        t1 = c.esq.tipo
        t2 = c.dir.tipo

        if t1 is None or t2 is None:
            c.tipo = None
            return

        # Operadores aritméticos: (int, int) -> int
        if op in ("+", "-", "*", "div"):
            if t1 is not TIPO_INT or t2 is not TIPO_INT:
                self._erro(f"Operador '{op}' exige operandos integer.")
                c.tipo = None
            else:
                c.tipo = TIPO_INT
            return

        # Operadores lógicos: (bool, bool) -> bool
        if op in ("and", "or"):
            if t1 is not TIPO_BOOL or t2 is not TIPO_BOOL:
                self._erro(f"Operador '{op}' exige boolean.")
                c.tipo = None
            else:
                c.tipo = TIPO_BOOL
            return

        # Operadores de diferença: (int, int) -> bool OU (bool, bool) -> bool
        if op in ("=", "<>"):
            if t1 is not t2:
                self._erro(f"Operador '{op}' exige operandos do mesmo tipo.")
                c.tipo = None
            else:
                c.tipo = TIPO_BOOL
            return

        # Operadores relacionais: (int, int) -> bool
        if op in ("<", "<=", ">", ">="):
            if t1 is not TIPO_INT or t2 is not TIPO_INT:
                self._erro(f"Operador '{op}' exige operandos integer.")
                c.tipo = None
            else:
                c.tipo = TIPO_BOOL
            return

        self._erro(f"Operador desconhecido '{op}'.")
        c.tipo = None

    def visita_CalculoUnario(self, c: ast.CalculoUnario):
        op = self._map_op(c.op)
        self.visita(c.calculo)

        t = c.calculo.tipo

        if t is None:
            c.tipo = None
            return
        # Operador unário 'not': (bool) -> bool
        if op == "not":
            if t is not TIPO_BOOL:
                self._erro("Operador 'not' exige boolean.")
                c.tipo = None
            else:
                c.tipo = TIPO_BOOL
            return
        # Operador unário '-': (int) -> -int
        if op == "-":
            if t is not TIPO_INT:
                self._erro("Operador unário '-' exige integer.")
                c.tipo = None
            else:
                c.tipo = TIPO_INT
            return

        self._erro(f"Operador unário desconhecido '{op}'.")
        c.tipo = None

    def visita_CalcId(self, idnode: ast.CalcId):
        simb = self.ts.busca(idnode.nome)
        if simb is None:
            self._erro(f"Variável '{idnode.nome}' não declarada.")
            idnode.tipo = None
        else:
            idnode.tipo = simb.tipo
            idnode.simbolo = simb

    def visita_CalcConstNum(self, c: ast.CalcConstNum):
        c.tipo = TIPO_INT

    def visita_CalcConstBool(self, c: ast.CalcConstBool):
        c.tipo = TIPO_BOOL