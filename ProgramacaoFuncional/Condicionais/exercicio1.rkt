#lang racket
(require examples)
;;Faça uma função que leia um número inteiro e diga se este número é menor que zero,
;;igual a zero ou maior que zero.
;;
;;Recebe numero real --> e retorna uma string

(define (<=>_que_zero numero)
  (cond
    [(> numero 0) "Maior que zero"]
    [(< numero 0) "Menor que zero"]
    [else "É zero"]
  )
)

(examples
  (check-equal? (<=>_que_zero 1) "Maior que zero")
  (check-equal? (<=>_que_zero -1) "Menor que zero")
  (check-equal? (<=>_que_zero 0) "É zero")
  (check-equal? (<=>_que_zero 0.017) "Maior que zero")
)