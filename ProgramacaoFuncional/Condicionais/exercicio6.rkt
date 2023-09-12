#lang racket
;;Calculo dos aumentos de salarios
;;-Receber o salario sendo um numero real com duas casa decimais 
;;-o percentual de aumento depende do salario atual
;;-Regras para os reajustes:
;;	-SALARIO <= 1200 aumento será de 10%
;;	-3000 => SALARIO > 1200 aumento será de 7%
;;	-8000 => SALARIO > 3000 aumento será de 3%
;;	-SALARIO > 8000 não haverá aumento

;;Teste de verificação de  veracidade
(require examples)
(examples
    (check-equal? (aumentoSalario 1100.00) 1210.00)
    (check-equal? (aumentoSalario 2500.00) 2675.00)
    (check-equal? (aumentoSalario 5000.00) 5150.00)
    (check-equal? (aumentoSalario 9300.00) 9300.00)
    )

(define (aumentoSalario salario)
        (cond
          [(<= salario 1200.00)(* 1.1 salario)]
          [(<= salario 3000.00)(* 1.07 salario)]
          [(<= salario 8000.00)(* 1.03 salario)]
          [(> salario 8000.00) salario]
         )
)