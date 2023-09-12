#lang racket

;Escreva uma função que retorne a área de um criculo único dado disponível é o seu raio.
;- Área = Pi * Raio * Raio

(define (areaCirculo raio) ( * (* raio raio) 3.14 ))
(areaCirculo 5)