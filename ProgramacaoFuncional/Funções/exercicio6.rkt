#lang racket
(require examples)

;Cada cidadão de um país, cuja moeda chama dinheiro, tem que pagar imposto sobre a sua renda.
;Cidadãos que recebem até 1000 dinheiros pagam 5% de imposto.
;Cidadãos que recebem entre 1000 e 5000 dinheiros pagam 5% de imposto sobre 1000 dinheiros e 10% sobre o que passar de 1000.
;Cidadãos que recebem mais do 5000 dinheiros pagam 5% de imposto sobre 1000 dinheiros, 10% de imposto sobre
;4000 dinheiros e 20% sobre o que passar de 5000.
;Projete uma função que calcule o imposto que um cidadão deve pagar dado a sua renda

(define (menos_que_mil renda)
  (* renda 0.05))

(define (entre_mil_e_cinco renda)
  (+ (* 1000 0.05)
     (* (- renda 1000) 0.10)))

(define (maior_que_cinco renda)
  (+
     (+ (* 1000 0.05)
        (* 4000 0.10))
     (* ( - renda 5000) 0.20)))

(define (imposto renda)
  (cond
    [(< renda 1000) (menos_que_mil renda)]
    [(and (>= renda 1000) (< renda 5000)) (entre_mil_e_cinco renda)]
    [else (maior_que_cinco renda)]))

(examples
(check-equal? (imposto 900) 45.0)
(check-equal? (imposto 2500) 200.0)
(check-equal? (imposto 7000) 850.0))