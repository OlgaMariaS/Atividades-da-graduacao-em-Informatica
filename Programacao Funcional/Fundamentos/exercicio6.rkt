#lang racket
(require examples)

;Escreva uma função que receba o raio r e retorne a área do circulo(Área = Pi * Raio * Raio).

;Tipo de dados trabalhos
;raio --> retornar area do circulo
;real positivo --> real positivo

(define (pi) 3.14)

(define (area_circulo raio)
  (if( > raio 0)
     (* (expt raio 2) 3.14)
     "Raio invalido")
)

(examples
  (check-equal? (area_circulo 10) 314.0)
  (check-equal? (area_circulo -1) "Raio invalido")
  (check-equal? (area_circulo 5) 78.5)
)