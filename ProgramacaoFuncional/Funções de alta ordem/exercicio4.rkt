#lang racket
;Reescreva as seguintes expressões usando let para remover as subexpressões em comum e
;melhorar a estrutura do código. Não faça nenhuma simplificação algébrica.

(define (conta a b)
  (let* ([3xa (* 3 a)]
        [-b (- 3xa b)]
        [+b (+ 3xa b)])
   (+ -b +b)))

(conta 2 3)

(define (lista lst)
  (let ([primeiro (first lst)]
        [resto (rest lst)])
  (cons primeiro resto)))

(lista (list 1 2 3 4))
