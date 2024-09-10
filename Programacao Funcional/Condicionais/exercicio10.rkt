#lang racket
(require examples)
 
;Faça uma função que receba a idade de um nadador e o classifique em uma das seguintes categorias:
;Idade              |Categoria
;5 ate 7 anos       |Infantil A
;8 ate 10 anos      |Infantil B
;11 ate 13 anos     |Juvenil A
;14 ate 17 anos     |Juvenil B
;Maiores de 18 anos |Adulto

;Tipo de dados
;idade  --> categoria
;numero inteiro positivo --> string

(define (classifica idade)
  (cond
    [(and (>= idade 5) (<= idade 7))  "Infantil A"]
    [(and (>= idade 8) (<= idade 10)) "Infantil B"]
    [(and (>= idade 11)(<= idade 13)) "Juvenil A"]
    [(and (>= idade 14)(<= idade 17)) "Juvenil B"]
    [(>= idade 18) "Adulto"]
    [else "Idade não pode ser classificada"]))

(examples
  (check-equal? (classifica 6) "Infantil A")
  (check-equal? (classifica 9) "Infantil B")
  (check-equal? (classifica 12) "Juvenil A")
  (check-equal? (classifica 15) "Juvenil B")
  (check-equal? (classifica 18) "Adulto")
  (check-equal? (classifica 3) "Idade não pode ser classificada")
)