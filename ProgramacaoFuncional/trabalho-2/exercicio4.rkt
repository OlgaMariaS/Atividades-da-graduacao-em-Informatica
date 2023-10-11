#lang racket
(require examples)
(struct pessoa (nome idade altura))

;a. Faça uma função que receba duas pessoas e retorne verdadeiro caso a
;primeira pessoa seja mais velha que a segunda, ou retorne falso, caso
;contário;
(define (a pessoa1 pessoa2)
  (cond
    [(> (pessoa-idade pessoa1) (pessoa-idade pessoa2)) #t]
    [else #f]))

;b. Faça uma função que receba duas pessoas e retorne verdadeiro caso a
;primeira pessoa seja mais alta que a segunda, ou retorne falso, caso
;contário;
(define (b pessoa1 pessoa2)
  (cond
    [(> (pessoa-altura pessoa1) (pessoa-altura pessoa2)) #t]
    [else #f]))

;c. Faça uma função que receba duas pessoas e retorne se o nome da
;primeira pessoa está alfabeticamente depois da segunda pessoa.
(define (c pessoa1 pessoa2)
  (cond
    [(string>? (pessoa-nome pessoa1) (pessoa-nome pessoa2)) #t]
    [else #f]))

;d. Faça uma função de alta ordem que receba uma lista de pessoas e uma
;função que compara duas pessoas, e retorne a lista de pessoas ordenada



(define pessoa1 (pessoa "Olga" 21 1.50))
(define pessoa2 (pessoa "Nilton" 25 1.80))

(examples
   (check-equal? (a pessoa1 pessoa2) #f)
   (check-equal? (a pessoa2 pessoa1) #t)
   (check-equal? (b pessoa1 pessoa2) #f)
   (check-equal? (b pessoa2 pessoa1) #t)
   (check-equal? (c pessoa1 pessoa2) #t)
   (check-equal? (c pessoa2 pessoa1) #f)
)