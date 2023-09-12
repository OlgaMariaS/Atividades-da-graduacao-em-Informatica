#lang racket
(require examples)
;;Faça uma função que receba um número e informe se ele é par ou impar
;;Receber numero real --> retorna string

(examples
  (check-equal? (par_impar 10) "Par")
  (check-equal? (par_impar 15) "Impar")
)

(define (par_impar numero)
  (cond
    [(equal? (remainder numero 2) 0) "Par"]
    [else "Impar"]
  )
 )