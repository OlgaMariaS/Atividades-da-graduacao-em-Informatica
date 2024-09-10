#lang racket
(require examples)
;Um sistema de folha de pagamento é utilizado por uma empresa para ter o processo de pagamento feito de maneira automática. Esse sistema precisa de
;uma função que dado um funcionário consegue calcular qual o salário bruto do mesmo. Esta empresa possui 3 tipos de funcionários:
;Os assalariados: são os funcionários que recebem um salário fixo todo mês.
;Os vendedores comissionados: são os funcionários que recebem um
;salário fixo, e quando ultrapassam uma meta de vendas, tem um acréscimo de 20% do valor que ultrapassou as vendas.
;Por exemplo, se um vendedor tem seu salário fixo R$ 1500,00, uma meta de R$ 5000,00 reais em venda, e vendeu um total de R$ 6000,00, este
;funcionário irá receber um total de R$ 1700,00, ou seja, 1500,00 do salário fixo somado a 20% de 1000,00 (valor que ultrapassou a comissão).
;Os horistas: são os funcionários que ganham por hora trabalhada. Sendo assim, seu salário é dado pelo valor de sua hora somado ao total de horas trabalhadas.
;Modele os dados para estes três tipos de funcionários e faça uma função em racket que receba um funcionário e retorne seu salário.

(struct assalariado (salario_bruto))
(struct vendedor (salario meta total_vendas))
(struct horista (valor_hora qtde_horas))

(define (calculo_vendedor dados)
  (if(> (- (vendedor-total_vendas dados) (vendedor-meta dados)) 0)
     (+ (vendedor-salario dados) (* (- (vendedor-total_vendas dados) (vendedor-meta dados)) 0.20))
     (vendedor-salario dados)))

;recebe o tipo de emprego -> salario (string->number)
(define (salario tipo_empregado dados)
  (cond
    [(equal? tipo_empregado "assalariado") (assalariado-salario_bruto dados)]
    [(equal? tipo_empregado "vendedor") (calculo_vendedor dados)]
    [(equal? tipo_empregado "horista") (* (horista-valor_hora dados) (horista-qtde_horas dados))]
    [else "Tipo empregado invalido"]
  )
)

(examples
 (check-equal? (salario "assalariado" (assalariado 1400)) 1400)
 (check-equal? (salario "vendedor" (vendedor 1500 5000 6000)) 1700.0)
 (check-equal? (salario "vendedor" (vendedor 1500 5000 4000)) 1500)
 (check-= (salario "horista" (horista 5.80 62)) 359.60 0.0001)
 (check-equal? (salario "rh" (vendedor 1500 5000 6000)) "Tipo empregado invalido")
)