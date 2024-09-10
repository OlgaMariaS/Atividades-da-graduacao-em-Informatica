#lang racket
(require examples)
;Defina uma função que receba como parâmetro um predicado (função de um argumento que retorna
;um valor booleano) e uma lista, e conte quantos elementos da lista satisfazem o predicado.

(define (satisfazem? predicado lista)
  (count predicado lista))

(examples
 (check-equal? (satisfazem? negative? '(0 1 2 -2 -5 -8)) 3)
 (check-equal? (satisfazem? zero? '(0 1 2 0 -5 -8)) 2)
 (check-equal? (satisfazem? natural? '(0 1 -3)) 2)
)