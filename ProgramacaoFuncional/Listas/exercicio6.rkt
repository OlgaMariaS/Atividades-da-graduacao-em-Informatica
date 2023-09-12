#lang racket
(require examples)
;Faça uma função que receba uma lista L e retorne uma lista M, onde o i-ésimo elemento de M é dado pelo fatorial do i-ésimo valor de L.

(define (fatorial n)
  (cond
   [(= n 1) 1]
   [else (* (fatorial (- n 1)) n)]))
         
(define (M L n)
  (cond
    [(empty? L) '()]
    [(equal? (first L) n) (cons (fatorial n) (M (rest L) n))]
    [else
      (cons (first L)
            (M (rest L) n))]))
     

(examples
 (check-equal? (M '(1 2 3 4) 4) '(1 2 3 24))
 (check-equal? (M '(4 7 8) 7) '(4 5040 8))
 (check-equal? (M '() 1) '())
 (check-equal? (M '(1 2) 3) '(1 2))
)
