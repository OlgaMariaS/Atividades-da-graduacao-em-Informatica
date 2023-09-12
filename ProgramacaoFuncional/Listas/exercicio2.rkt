#lang racket
(require examples)
;A série de Fibonacci é uma série onde o termo I é a soma do termo I-1 com I-2 (Ti = Ti-1 + Ti-2). Tal série tem inicio nos termos 0 e 1 (T1=0 T2=1). Faça uma
;função que receba um valor N e retorne qual o valor do N-ésimo termo (TN) da série de Fibonacci.
;Série de Fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, 21....

(define (fibonacci n)
  (cond
    [(equal? n 0) 0]
    [(equal? n 1) 1]
    [else
     (+
      (fibonacci (- n 1))
      (fibonacci (- n 2)))
    ]))

(examples
 (check-equal? (fibonacci 2) 1)
 (check-equal? (fibonacci 6) 8)
 (check-equal? (fibonacci 0) 0)
)
