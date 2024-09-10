#lang racket
(require examples)
;Defina uma função simule um caixa eletrônico. Sua função deve receber um valor a ser
;sacado e uma lista de notas (em ordem decrescente). O retorno da função deve ser a
;menor lista contendo as notas a serem usadas para totalizar o valor. Caso não seja
;possível totalizar o valor, deve ser retornada uma lista vazia.

(define (caixa-eletronico valor-a-sacar notas-solicitadas)
  (define (cria-lista-notas valor notas)
    (cond
      [(or (equal? valor 0) (empty? notas)) empty]
      [(> (quotient valor (first notas)) 0)
       (cons (first notas) 
             (cria-lista-notas (- valor (first notas)) notas))]
      [else (cria-lista-notas valor (rest notas))]))
  
  (define (notas-são-validas? valor-atingir lista-notas)
    (cond
      [(empty? lista-notas) empty]
      [(equal? valor-atingir (foldr + 0 lista-notas)) lista-notas]
      [else (notas-são-validas? valor-atingir (cria-lista-notas valor-a-sacar (rest notas-solicitadas)))]))

  (notas-são-validas? valor-a-sacar (cria-lista-notas valor-a-sacar notas-solicitadas)))
  
(examples 
 (check-equal? (caixa-eletronico 397 (list 100 50 20 10 2 1)) '(100 100 100 50 20 20 2 2 2 1))
 (check-equal? (caixa-eletronico 0 (list 50 20 10)) '())
 (check-equal? (caixa-eletronico 160 (list 50 20 10)) '(50 50 50 10))
 ;(check-equal? (caixa-eletronico 101 (list 100 50 20 10 5)) '())
 ;(check-equal? (caixa-eletronico 101 (list 100 50 20 10 5 2)) '(50 20 20 5 2 2 2))
 (check-equal? (caixa-eletronico 101 (list 100 50 20 10 5 2 1)) '(100 1))
)
