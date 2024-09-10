#lang racket
(require examples)
;Faça um função para receber a idade de uma pessoa e informar:
;-Se ela é maior de idade;
;-Se ela é menor de idade;
;-Se ela tem mais de 65 anos;

;Recebe um numero inteiro, a idade verifica se é maior que 18 anos, se for verifica se é maior que 65 (Idoso)
;caso não seja maior de 18 é menor de idade

(examples
  (check-equal? (etaridade 21) "maior de idade")
  (check-equal? (etaridade 15) "menor de idade")
  (check-equal? (etaridade 72) "Idoso")
)

(define (etaridade idade)
  (cond
    [(> idade 18)
     (if(> idade 65) "Idoso"
     "maior de idade") ]
    [else "menor de idade"]
  )
)
