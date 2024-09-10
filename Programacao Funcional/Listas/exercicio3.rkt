#lang racket
(require examples)
;Faça uma função que receba um número inteiro e conte quantos dígitos esse número tem

(define (conta-n n)
  (string-length(number->string n))
)

(examples
 (check-equal? (conta-n 1234) 4)
 (check-equal? (conta-n 111) 3)
 (check-equal? (conta-n 9) 1)
)
