#lang racket
(require examples)
 
;Faça uma função que receba um valor para x e retorne o valor de f(x):

;Tipo de dados
;x  --> f(x)
;real --> inteiro positivo

(define (f_de_x x)
  (cond
    [(<= x 1) 1]
    [(and (> x 1) (<= x 2)) 2]
    [(and (> x 2) (<= x 3)) (expt x 2)]
    [else
     (expt x 3)]))

(examples
  (check-equal? (f_de_x -1) 1)
  (check-equal? (f_de_x 1.5) 2)
  (check-equal? (f_de_x 3) 9)
  (check-equal? (f_de_x 5) 125)
)