#lang racket
(require examples)
;;Faça uma função para ler um número e, se ele for maior do que 20, então retornar a
;;metade do número, caso contrario, retonar o próprio número.

;;Recebe numero real --> retorna numero real
(examples
  (check-= (maior_que_20 42) 21 0)
    (check-= (maior_que_20 26.17) 13.085 0)
  (check-= (maior_que_20 15) 15 0)
)

(define (maior_que_20 numero)
  (cond
    [(> numero 20) (/ numero 2)]
    [else numero]
  )
)