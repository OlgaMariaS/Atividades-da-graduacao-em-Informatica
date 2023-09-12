#lang racket
(require examples)

;Elabore uma função para calcular e retornar o volume de um cilindro de raio r e altura A utilizando a fórmula: V = 3.14159. (r. r). A

;Tipo de dados
;raio e altura --> volume do cilindro
;real positivo --> real positivo

(define (volume_cilindro raio alt)
  (if(and (> raio 0) (> alt 0))
    (* 3.14159 (*(expt raio 2) alt))
     "Dados invalidos"))

(examples
  (check-equal? (volume_cilindro 3 15) 424.11465)
  (check-equal? (volume_cilindro -1 0) "Dados invalidos")
  (check-equal? (volume_cilindro 5 4) 314.159)
  (check-equal? (volume_cilindro 5 0) "Dados invalidos")
)