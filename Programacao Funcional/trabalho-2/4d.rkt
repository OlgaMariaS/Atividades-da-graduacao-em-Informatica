#lang racket
(require examples)
(struct pessoa (nome idade altura))

;d. Faça uma função de alta ordem que receba uma lista de pessoas e uma
;função que compara duas pessoas, e retorne a lista de pessoas ordenada
(define (fator-nome p1 p2)
  (string<? (pessoa-nome p1) (pessoa-nome p2)))
(define (fator-idade p1 p2)
  (< (pessoa-idade p1) (pessoa-idade p2)))
(define (fator-altura p1 p2)
  (< (pessoa-altura p1) (pessoa-altura p2)))

(define (ordena lista fator-ordem)
  (sort lista fator-ordem))

(define pessoa1 (pessoa "Olga" 21 1.50))
(define pessoa2 (pessoa "Nilton" 25 1.80))
(define lista-pessoas (list pessoa1 pessoa2 (pessoa "José" 29 1.80) (pessoa "Bianca" 17 1.70) (pessoa "Gabriel" 19 1.68)))

(define (exibe-lista lst)
  (for-each (lambda (p) (display (pessoa-nome p)) (display " ") (display (pessoa-idade p)) (display " ") (display (pessoa-altura p)) (display " | ")) lst))

; Exibe a lista ordenada
(display "Ordenado por nome: ")
(exibe-lista (ordena lista-pessoas fator-nome))
(newline)
(display "Ordenado por idade: ")
(exibe-lista (ordena lista-pessoas fator-idade))
(newline)
(display "Ordenado por altura: ")
(exibe-lista (ordena lista-pessoas fator-altura))
