#lang racket
(require examples)
;Considerando que se deseja representar as seguintes figuras: retângulos;trapézios; e círculos.
;Além disso, também se deseja ter uma função que receba uma figura e retorne o valor de sua área.
;a. Faça a representação dos três tipos de figuras em racket.
;b. Faça uma função que receba uma figura e calcule sua área.

(struct retangulo (base alt))
(struct trapezio (baseMaior baseMenor alt))
(struct circulo (raio))
(define (pi) 3.14)

;recebe o tipo de figura -> area (string->number)
(define (calcula_area figura dados)
  (cond
    [(equal? figura "retangulo") (* (retangulo-base dados) (retangulo-alt dados))]
    [(equal? figura "trapezio") (/ (* (+ (trapezio-baseMaior dados) (trapezio-baseMenor dados)) (trapezio-alt dados)) 2)]
    [(equal? figura "circulo") (* (expt (circulo-raio dados) 2) (pi))]
    [else "figura invalida"]
  )
)

(examples
 (check-equal? (calcula_area "retangulo" (retangulo 10 15)) 150)
 (check-equal? (calcula_area "trapezio" (trapezio 4 2 5)) 15)
 (check-equal? (calcula_area "circulo" (circulo 5)) 78.5)
)