#lang racket
(require examples)

;Escreva a especificação para a seguinte implementação de função. Observe que a especificação sozinha deve ser suficiente para um programador fazer uma implementação.

;Especificação: Crie um código que receba uma palavra e substitua as letras "a" e "b" por 0 e 1, respectivamente;
;após substituir converta a string em numero com base binaria, caso retorne um numero a string era composto somente por a e b, caso não, era falso, haviam mais letras

;string -> numero ou booleano

(define (ab->number s)
  (string->number (string-replace (string-replace s "a" "0" ) "b" "1") 2))

(examples
(check-equal? (ab->number "Olga") #f)
(check-equal? (ab->number "abba") 6)
(check-equal? (ab->number "banana") #f))
