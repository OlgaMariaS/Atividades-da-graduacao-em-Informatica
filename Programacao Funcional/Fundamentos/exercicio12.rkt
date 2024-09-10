#lang racket
(require examples)

;Faça uma função que receba 4 números e retorne a média ponderada, sabendo-se que os pesos são respectivamente: 1, 2, 3 e 4.

;Tipo de dados
;numeros  --> media ponderada
;real positivo --> real positivo

(define (multiplica x y)
  (* x y))

(define (peso)
  (+ 4(+ 3 (+ 2 1))))
  
(define (media_ponderada n1 n2 n3 n4)
  (/
   (+ (multiplica n4 4)
       (+ (multiplica n3 3)
          (+ (multiplica n1 1) (multiplica n2 2))))
  (peso)
  )
)

(examples
  (check-equal? (media_ponderada 1 2 3 4) 3)
  (check-equal? (media_ponderada 5 5 7.5 8) 6.95)
  (check-equal? (media_ponderada 10 2.1 4.4 6) 5.14)
)