#lang racket
(require examples)
;Faça uma função de alta ordem que receba uma operação binária e comutativa
;(que recebe dois operandos e o resultado não é alterado de acordo com a ordem deles),
;um valor inicial e uma lista aninhada operandos e aplique esta operação em todos os números da lista aninhada.

;Função, numero, lista --> numero 
(define (foldr op caso-base lista)
  (cond
    [(empty? lista) caso-base]
    [(list? (first lista)) 
            (op (foldr op caso-base (first lista))
                  (foldr op caso-base (rest lista)))]
    [else (op (first lista) (foldr op caso-base (rest lista)))]))

(define (aplicar-operacao op caso-base lista)
  (foldr op caso-base lista))

;Operações comutativas, somente adição e multiplicação
;função -> numero
(define (caso-base op)
  (cond
    [(equal? op +) 0]
    [(equal? op *) 1]
    [else "Não é comutativa"]))

(examples
 (check-equal? (aplicar-operacao + (caso-base +) empty) 0)
 (check-equal? (aplicar-operacao + (caso-base +) (list (list 1 (list empty 3)) (list 4 5) 4 6 7)) 30)
 (check-equal? (aplicar-operacao * (caso-base *) (list '((1 (3 4)) (4 5) 6 2))) 2880)
 (check-equal? (aplicar-operacao * (caso-base *) (list )) 1)
)

