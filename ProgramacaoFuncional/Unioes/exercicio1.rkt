#lang racket
(require examples)
;Um sistema possui a capacidade de cadastrar clientes como sendo pessoas físicas e pessoas jurídicas.
;Considerando essas informações, utilizando a linguagem racket, faça o seguinte:
;a. Modele os dados para pessoa física e pessoa jurídica.
;b. Faça uma função que receba uma pessoa e retorne se ela é uma pessoa física ou jurídica
;c. Neste sistema, será necessário o uso de uma função para avaliar qual o valor máximo da prestação mensal do empréstimo a ser concedido uma
;pessoa. Para pessoas físicas, o valor da prestação deve ser no máximo 50% do salário bruto mensal da pessoa. Para pessoas jurídicas, o valor da
;prestação deve ser no máximo 20% do faturamento anual da empresa. Faça uma função que receba uma pessoa e retorne o valor máximo da prestação que esta pessoa pode pagar.

(struct pf (nome CPF cidade endereco salario_bruto))
(struct pj (razao_social nome_fant cnpj cidade endereco faturamento))

;recebe o tipo de pessoa -> valor da prestação (string->number)
(define (max_prestacao tipo_pessoa dados_pessoa)
  (cond
    [(equal? tipo_pessoa "pf") (* (pf-salario_bruto dados_pessoa) 0.5)]
    [else (* (pj-faturamento dados_pessoa) 0.2) ]))

(examples
 (check-equal? (max_prestacao "pf" (pf "Olga" 07342864900 "Maringa" "R Quintinho" 2500)) 1250.0)
 (check-equal? (max_prestacao "pj" (pj "FLJ" "Flsoft" 02653153000163 "Apucarana" "R Munhoz" 1000000)) 200000.0)
)