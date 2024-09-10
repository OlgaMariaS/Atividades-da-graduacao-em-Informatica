#lang racket
(require examples)
(struct pessoa (nome idade altura))

;a. Faça uma função que receba duas pessoas e retorne verdadeiro caso a
;primeira pessoa seja mais velha que a segunda, ou retorne falso, caso
;contário;
(define (a pessoa1 pessoa2)
  (cond
    [(>= (pessoa-idade pessoa1) (pessoa-idade pessoa2)) #t]
    [else #f]))

;b. Faça uma função que receba duas pessoas e retorne verdadeiro caso a
;primeira pessoa seja mais alta que a segunda, ou retorne falso, caso
;contário;
(define (b pessoa1 pessoa2)
  (cond
    [(>= (pessoa-altura pessoa1) (pessoa-altura pessoa2)) #t]
    [else #f]))

;c. Faça uma função que receba duas pessoas e retorne se o nome da
;primeira pessoa está alfabeticamente depois da segunda pessoa.
(define (c pessoa1 pessoa2)
  (cond
    [(string>? (pessoa-nome pessoa1) (pessoa-nome pessoa2)) #t]
    [else #f]))

;d. Faça uma função de alta ordem que receba uma lista de pessoas e uma
;função que compara duas pessoas, e retorne a lista de pessoas ordenada
(define (fator-nome p1 p2)
  (string<? (pessoa-nome p1) (pessoa-nome p2)))
(define (fator-idade p1 p2)
  (<= (pessoa-idade p1) (pessoa-idade p2)))
(define (fator-altura p1 p2)
  (<= (pessoa-altura p1) (pessoa-altura p2)))

(define (exibe-lista lst)
  (for-each (lambda (p) (display (pessoa-nome p)) (display " ") (display (pessoa-idade p)) (display " ") (display (pessoa-altura p)) (display " | ")) lst))
;---------------------------------------------------------------------------

(define pessoa1 (pessoa "Olga" 21 1.50))
(define pessoa2 (pessoa "Nilton" 25 1.80))
(define lista-pessoas (list pessoa1 pessoa2 (pessoa "José" 29 1.80) (pessoa "Bianca" 27 1.70) (pessoa "Gabriel" 19 1.68)))

(examples
   (check-equal? (a pessoa1 pessoa2) #f)
   (check-equal? (a pessoa2 pessoa1) #t)
   (check-equal? (b pessoa1 pessoa2) #f)
   (check-equal? (b pessoa2 pessoa1) #t)
   (check-equal? (c pessoa1 pessoa2) #t)
   (check-equal? (c pessoa2 pessoa1) #f)
)
; Exibe a lista ordenada
(display "Ordenado por nome: ")
(exibe-lista (sort lista-pessoas fator-nome))
(newline)
(display "Ordenado por idade: ")
(exibe-lista (sort lista-pessoas fator-idade))
(newline)
(display "Ordenado por altura: ")
(exibe-lista (sort lista-pessoas fator-altura))
(newline)