#lang racket
(require examples)
;Faça uma função que receba uma lista L e um valor natural n, e retorne uma lista contendo os n primeiros elementos de L.
;Quando n for maior que o tamanho da lista, retorne a lista toda.

(define (imprime_n lista n)
  (cond
    [(or (empty? lista) (equal? n 0)) '()]
    [else
     (cons (first lista)(imprime_n (rest lista) (- n 1)))
    ]))

(examples
 (check-equal? (imprime_n '(1 2 3 4) 2) '(1 2))
 (check-equal? (imprime_n '(1 2 3 4) 6) '(1 2 3 4))
 (check-equal? (imprime_n '() 2) '())
)
