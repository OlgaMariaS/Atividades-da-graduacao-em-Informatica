from __future__ import annotations
from dataclasses import dataclass
from typing import List
from utils import Tipo, Simbolo

class No: ...

class Cmd(No): ...

class Calculo(No):
    tipo: Tipo | None = None

# ----------------------------------------------------------------------
# PROGRAMA e BLOCO
# ----------------------------------------------------------------------

@dataclass
class Programa(No):
    nome: str
    bloco: Bloco
    total_vars: int = 0   # preenchido pelo analisador semântico

@dataclass
class Bloco(No):
    declaracoes: List[Declaracao]
    comando: Cmd   # comando_composto

# ----------------------------------------------------------------------
# DECLARAÇÕES
# ----------------------------------------------------------------------

@dataclass
class Declaracao(No):
    nomes: List[str]      # lista_identificadores
    tipo: str             # "integer" ou "boolean"

# ----------------------------------------------------------------------
# COMANDOS
# ----------------------------------------------------------------------

@dataclass
class BlocoCmds(Cmd):
    lista_cmds: List[Cmd]

@dataclass
class Atribuicao(Cmd):
    id: CalcId
    calculo: Calculo

@dataclass
class Condicional(Cmd):
    condicao: Calculo
    bloco_then: Cmd
    bloco_else: Cmd | None

@dataclass
class Repeticao(Cmd):
    condicao: Calculo
    corpo: Cmd

@dataclass
class Leitura(Cmd):
    ids: List[CalcId]

@dataclass
class Escrita(Cmd):
    exprs: List[Calculo]

# ----------------------------------------------------------------------
# EXPRESSÕES
# ----------------------------------------------------------------------

@dataclass
class CalculoBinario(Calculo):
    esq: Calculo
    op: str
    dir: Calculo

@dataclass
class CalculoUnario(Calculo):
    op: str
    calculo: Calculo

@dataclass
class CalcId(Calculo):
    nome: str
    simbolo: Simbolo | None = None

@dataclass
class CalcConstNum(Calculo):
    valor: int

@dataclass
class CalcConstBool(Calculo):
    valor: bool
