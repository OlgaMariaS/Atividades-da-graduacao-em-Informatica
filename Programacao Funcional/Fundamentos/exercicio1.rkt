#lang racket
;Faça uma função que receba dois número e gere a média aritmética

(define (soma n1 n2) (+ n1 n2))
(define (media x1 x2) (/ (soma x1 x2) 2))

(media 7 3)