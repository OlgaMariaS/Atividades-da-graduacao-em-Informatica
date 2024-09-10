#lang racket
(require examples)
(struct no (valor esq dir) #:transparent)

;Projete uma função que verifique se uma árvore binária é uma árvore binária de busca.
;Uma árvore binária de busca tem as seguintes propriedades:
;1) A subárvore a esquerda contém valores nos nós menores que o valor no nó raiz.
;2) A subárvore a direita contém valores nos nós maiores que o valor no nó raiz.
;3) As subárvores a esquerda e a direita também são árvores binárias de busca.

(define (eh-arv-busca? arv)
  (cond
    [(empty? arv) "arvore binaria de BUSCA"]
    [(and (> (no-valor arv) (no-valor (no-esq arv)))
          (< (no-valor arv) (no-valor (no-dir arv))))
     (eh-arv-busca? (no-esq arv)) (eh-arv-busca? (no-dir arv))]
    [else "arvore vazia"]))
          
(define arvore (no 5 (no 2 (no 1 empty empty) (no 4 empty empty))
                     (no 7 (no 6 empty empty) (no 10 empty empty))))
;     5
;  2     7
;1  4  6  10

(eh-arv-busca? arvore)