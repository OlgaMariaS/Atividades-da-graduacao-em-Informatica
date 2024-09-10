#lang racket
(require examples)
;Defina uma função de alta ordem chamada scan. Sua função deverá receber uma função
;de dois argumentos f, um valor inicial ini e uma lista lst, sendo os valores de lst e o
;valor ini operandos validos para a operação f. Por fim, sua função deverá retornar uma
;lista S onde o i-ésimo elemento de S é dado pela operação f aplicada ao valor ini e todos
;os elementos das posições 1 até i da lista lst. Não é permitido que sua função faça recomputações.

;a função scan, aplica a função f no first da lst e ini, depois é chamado a função scan,
;passando o rest da lista, e o novo ini será o retorno do valor de f aplicada a ini e first da lst,
;assim até que chegue ao fim de lst

;Recebe um função, valor, lista --> lista
(define (scan f ini lst)
  (cond
    [(empty? lst) empty]
    [else (let ([valor-inicial (f ini (first lst))])
            (cons valor-inicial
                (scan f valor-inicial (rest lst))))]))

(examples
 (check-equal? (scan + 2 '(9 3 1 7)) '(11 14 15 22))
 (check-equal? (scan + 2 (list 9 3 1 7)) '(11 14 15 22))
 (check-equal? (scan * 1 (list 2 3 5)) '(2 6 30))
 (check-equal? (scan append (list ) (list (list 1 2) (list 3) (list 4 5))) '((1 2) (1 2 3) (1 2 3 4 5)))
 (check-equal?(scan append (list 0) (list (list 1 2) (list 3) (list 4 5))) '((0 1 2) (0 1 2 3) (0 1 2 3 4 5)))
)