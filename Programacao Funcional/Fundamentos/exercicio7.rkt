#lang racket
(require examples)

;Criar uma função que receba os valores da diagonal maior, diagonal menor e calcule e retorne a área de um losango.
;A =(D x d) / 2. Onde A é a área, D é a diagonal maior e d a diagonal menor

;Tipo de dados
;diagonais --> area do losango
;real positivo --> real positivo

(define (area_losango D d)
  (if(and (> D 0) (> d 0))
     (/ (* D d) 2)
     "Diagonais invalidas"))

(examples
  (check-equal? (area_losango 10 5) 25)
  (check-equal? (area_losango -1 0) "Diagonais invalidas")
  (check-equal? (area_losango 5 4) 10)
  (check-equal? (area_losango 5 0) "Diagonais invalidas")
)