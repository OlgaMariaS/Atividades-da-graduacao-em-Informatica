#lang racket
(require examples)
;A conjectura de Goldbach diz que todo número par maior que 4 pode ser escrito pela
;soma de dois números primos. Faça uma função que receba um número par maior que 4
;e retorne uma lista composta por listas de dois números primos compõem a soma
;(quando existirem diversas combinações, deve-se retornar todas). Caso o número não
;seja par ou não seja maior que 4, deverá ser retornada uma lista vazia.

;Função que verifica primo
(define (primo? n) )

;Recebe numero -> retorna lista aninhada
(define (goldbach n)
  (cond
    [(< n 4) '()]
    [(> (remainder n 2) 0) '()]
    [else 
    

(examples
 (check-equal? (goldbach 16) '((3 13) (5 11) (11 5) (13 3)))
 (check-equal? (goldbach 20) '((3 17) (7 13) (13 7) (17 3)))
 (check-equal? (goldbach 4) '((2 2)))
 (check-equal? (goldbach 2) '())
 (check-equal? (goldbach 15) '())
 (check-equal? (goldbach 22) '((3 19) (5 17) (11 11) (17 5) (19 3)))
)
 
 


