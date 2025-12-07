from __future__ import annotations
from dataclasses import dataclass
import AST as ast

class Tipo: ...

@dataclass(frozen=True)
class TipoInt(Tipo):
    def __str__(self) -> str:
        return "integer"

@dataclass(frozen=True)
class TipoBool(Tipo):
    def __str__(self) -> str:
        return "boolean"

TIPO_INT = TipoInt()
TIPO_BOOL = TipoBool()

class Categoria:
    VAR = 'var'
    PROG = 'programa'

@dataclass
class Simbolo:
    nome: str
    cat: str
    tipo: Tipo | None = None
    deslocamento: int = 0

# Visitor genérico
class Visitador:
    def visita(self, no: ast.No):
        if no is None:
            return
        nome_metodo = f'visita_{type(no).__name__}'
        visitor = getattr(self, nome_metodo, self.visita_padrao)
        return visitor(no)

    def visita_padrao(self, no: ast.No):
        raise NotImplementedError(f"visita_{type(no).__name__} não foi implementada.")