#lang racket
(require examples)

;Escreva a especificação para a seguinte implementação de função.
;Observe que a especificação sozinha deve ser suficiente para um programador fazer uma implementação.

;Especificação: crie um código que receba um nome e verifique se o nome é curto (menor ou igual a 4 letras)
;se é médio (menor ou igual a 10 letras) ou longo (maior que 10 letras)

(define (tamanho-nome nome)
  (cond
    [(<= (string-length nome) 4) "curto"]
    [(<= (string-length nome) 10) "médio"]
    [else "longo"]))

(examples
(check-equal? (tamanho-nome "Olga") "curto")
(check-equal? (tamanho-nome "Augusto") "médio")
(check-equal? (tamanho-nome "Maria Isabele") "longo"))
