#lang racket
(require examples)
 
;A Chevrolet abriu uma linha de crédito para compra de carros aos seus clientes. O valor máximo da prestação não poderá ultrapassar 40% do salário bruto.
;Faça uma função que receba o salário bruto e o valor da prestação e retorne se o emprestimo pode ou não ser concedido

;Tipo de dados
;salario, valor prestação  --> concede ou não concede
;numero real --> string

(define (max_prestacao salario)
  (* salario 0.4))

(define (concede_emprestimo? salario prestacao)
  (if(> (max_prestacao salario) prestacao) "Concedido" "Não concedido"))

(examples
  (check-equal? (concede_emprestimo? 1000 350) "Concedido")
  (check-equal? (concede_emprestimo? 1000 401) "Não concedido")
)