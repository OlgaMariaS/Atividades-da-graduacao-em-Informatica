#lang racket
(require examples)
;Faça um programa que receba um valor N, sendo N um inteiro maior que 0 e retorne uma lista contendo cada digito N.

(define (numero->lista n lista)
  (cond
    [(= n 0) lista]
    [else
      (numero->lista (quotient n 10) (cons (remainder n 10) lista))]))
     

(examples
 (check-equal? (numero->lista 1234 '()) '(1 2 3 4))
 (check-equal? (numero->lista 111 '()) '(1 1 1))
 (check-equal? (numero->lista 92 '()) '(9 2))
)
