#lang racket
(require examples)
;Luiz irá começar a investir uma parte fixa do seu salário todo mês. Ele pediu sua ajuda
;para resolver duas situações:

;a. Sabe-se que ele depositará em sua aplicação uma quantia de r reais todos os
;meses. Além disso, a aplicação na qual Luiz está investindo tem um rendimento
;mensal fixo de p% ao mês. Faça uma função que calcule o tempo (em meses)
;necessários para que Luiz ultrapasse o montante de m Reais, o qual também
;deve ser informado a função.
;Recebe tres valores --> um numero, sendo tempo
(define (tempo-para-montante r p m)
  (define % (+ 1 (/ p 100)))
  
  (define (calculo-montante total meses)
    (cond
      [(>= total m) meses]
      [(= meses 1) (calculo-montante (* total %) (add1 meses))]
      [else (calculo-montante (* (+ r total) %) (add1 meses))])) 

  (calculo-montante r 0))

;b. Além disso, ele quer saber quanto ele teria ao fim de um determinado periodo
;de tempo t meses, se mantivesse esse deposito de r reais mensais com
;rendimento de p% ao mes. Sendo assim, projete uma função receba r, p e t e
;retorne o valor total acumulado ao final do periodo de tempo.
(define (total-acumulado r p t)
  (define % (+ 1 (/ p 100)))

  (define (calculo total meses)
    (cond
      [(= meses t) total]
      [(= meses 1) (calculo (* total %) (add1 meses))]
      [else (calculo (* (+ total r) %) (add1 meses))]))
  
  (calculo r 0))

(examples
 (check-equal? (tempo-para-montante 100.0 3 1500.0) 13)
 (check-= (total-acumulado 100.0 3 13) 1612.0 1)
)