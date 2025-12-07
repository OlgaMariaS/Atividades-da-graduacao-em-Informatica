from __future__ import annotations
from typing import List
import AST as ast
from utils import Visitador

NIVEL_LEXICO = 0

class GeradorDeCodigo(Visitador):
    # Mapa de operadores para instruções MEPA
    MEPA_OP = {
        '+': 'SOMA',
        '-': 'SUBT',
        '*': 'MULT',
        'div': 'DIVI',
        'and': 'CONJ',
        'or': 'DISJ',
        '=': 'CMIG',
        '<>': 'CMDG',
        '<': 'CMME',
        '<=': 'CMEG',
        '>': 'CMMA',
        '>=': 'CMAG'
    }

    MEPA_OP_UNARIO = {
        'not': 'NEGA',
        '-': 'INVR'
    }

    def __init__(self):
        self.codigo: List[str] = []
        self.erros: List[str] = []
        self.tem_erro = False
        self.contador_rotulos: int = 0

    def _erro(self, msg: str):
        self.erros.append(f"Erro de geração: {msg}")
        self.tem_erro = True

    def _emite(self, instrucao: str):
        self.codigo.append(f"{instrucao}")

    def _emite_rotulo(self, rotulo: str):
        self.codigo.append(f"{rotulo}: NADA")

    def _novo_rotulo(self) -> str:
        rotulo = f"R{self.contador_rotulos:02d}"
        self.contador_rotulos += 1
        return rotulo

    def _normaliza_op(self, op: str) -> str:
        """
        Normaliza operadores que às vezes chegam como tokens distintos.
        Ex.: 'DIV'/'div' -> 'div', 'DIF' -> '<>', etc.
        """
        if op is None:
            return op
        mapa_norm = {
            "DIF": "<>",
            "<>": "<>",
            "LESS": "<=",
            "<=": "<=",
            "GREATER": ">=",
            ">=": ">=",
            "AND": "and",
            "OR": "or",
            "DIV": "div",
        }
        if op in mapa_norm:
            return mapa_norm[op]
        low = op.lower() if isinstance(op, str) else op
        return low if isinstance(low, str) else op

    # PROGRAMA E BLOCO
    def visita_Programa(self, prog: ast.Programa):
        # inicialização
        self._emite("INPP")
        # aloca memória para variáveis
        if getattr(prog, "total_vars", 0) > 0:
            self._emite(f"AMEM {prog.total_vars}")
        self.visita(prog.bloco)
        # finalização
        if prog.total_vars > 0:
            self._emite(f"DMEM {prog.total_vars}")
        self._emite("PARA")
        self._emite("FIM")

    def visita_Bloco(self, bloco: ast.Bloco):
        self.visita(bloco.comando)

    # COMANDO COMPOSTO
    def visita_BlocoCmds(self, bloco: ast.BlocoCmds):
        for cmd in bloco.lista_cmds:
            self.visita(cmd)

    def visita_Declaracao(self, decl: ast.Declaracao):
        pass

    def visita_Atribuicao(self, cmd: ast.Atribuicao):
        self.visita(cmd.calculo)
        # armazena no endereço da variável
        simbolo = getattr(cmd.id, "simbolo", None)
        if simbolo is None or simbolo.deslocamento is None:
            self._erro(f"Deslocamento não encontrado para '{cmd.id.nome}' na atribuição.")
            return
        self._emite(f"ARMZ {NIVEL_LEXICO},{simbolo.deslocamento}")

    def visita_Condicional(self, cmd: ast.Condicional):
        rot_else = self._novo_rotulo()
        rot_fim  = self._novo_rotulo()

        self.visita(cmd.condicao)
        
        if cmd.bloco_else:
            self._emite(f"DSVF {rot_else}")
            self.visita(cmd.bloco_then)
            self._emite(f"DSVS {rot_fim}")

            self._emite_rotulo(rot_else)
            self.visita(cmd.bloco_else)
        else:
            # se não tem else, desvia para fim
            self._emite(f"DSVF {rot_fim}")
            self.visita(cmd.bloco_then)

        self._emite_rotulo(rot_fim)

    def visita_Repeticao(self, cmd: ast.Repeticao):
        rot_inicio = self._novo_rotulo()
        rot_fim = self._novo_rotulo()

        self._emite_rotulo(rot_inicio)
        self.visita(cmd.condicao)

        # se falso -> fim
        self._emite(f"DSVF {rot_fim}")
        self.visita(cmd.corpo)
        # volta para início
        self._emite(f"DSVS {rot_inicio}")
        self._emite_rotulo(rot_fim)

    def visita_Leitura(self, cmd: ast.Leitura):
        # para cada id: LEIT; ARMZ 0,deslocamento
        for idnode in cmd.ids:
            simbolo = getattr(idnode, "simbolo", None)
            if simbolo is None or simbolo.deslocamento is None:
                self._erro(f"Variável '{idnode.nome}' não anotada para READ.")
                continue
            self._emite("LEIT")
            self._emite(f"ARMZ {NIVEL_LEXICO},{simbolo.deslocamento}")

    def visita_Escrita(self, cmd: ast.Escrita):
        for expr in cmd.exprs:
            self.visita(expr)
            self._emite("IMPR")

    # EXPRESSÕES
    def visita_CalculoBinario(self, calc: ast.CalculoBinario):
        self.visita(calc.esq)
        self.visita(calc.dir)

        op = self._normaliza_op(calc.op)

        mepa = self.MEPA_OP.get(op, None)
        if mepa is None:
            self._erro(f"Operador binário desconhecido para geração: '{calc.op}' (normalizado: '{op}')")
            return
        self._emite(mepa)

    def visita_CalculoUnario(self, calc: ast.CalculoUnario):
        self.visita(calc.calculo)
        op = self._normaliza_op(calc.op)
        mepa = self.MEPA_OP_UNARIO.get(op, None)
        if mepa is None:
            self._erro(f"Operador unário desconhecido para geração: '{calc.op}' (normalizado: '{op}')")
            return
        self._emite(mepa)

    def visita_CalcId(self, idnode: ast.CalcId):
        simbolo = getattr(idnode, "simbolo", None)
        if simbolo is None or simbolo.deslocamento is None:
            self._erro(f"ID '{idnode.nome}' sem deslocamento.")
            return
        self._emite(f"CRVL {NIVEL_LEXICO},{simbolo.deslocamento}")

    def visita_CalcConstNum(self, const: ast.CalcConstNum):
        self._emite(f"CRCT {const.valor}")

    def visita_CalcConstBool(self, const: ast.CalcConstBool):
        valor_mepa = 1 if const.valor else 0
        self._emite(f"CRCT {valor_mepa}")