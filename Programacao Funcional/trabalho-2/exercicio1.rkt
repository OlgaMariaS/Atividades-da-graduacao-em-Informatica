#lang racket
(require examples)

;Faça uma função em racket que receba 3 valores inteiros positivos, A, B e C.
;Sua função deverá retornar a soma de todos os números no intervalo [A, B] que
;são divisíveis por C. Caso A seja maior que B, seu programa deverá retornar o valor 0.
;--------------------------------------------------------------------------------------
;Tipo de dados trabalhos
;3 valores --> uma soma ou 0
;Numeros inteiro -> Numero inteiro 

;Primeiro verificarmos se A é maior que B, depois se A é divisivel por C, ou seja (resto da divisão de A por C é igual a 0)
;caso seja, será somado, e iremos pro proximos de A, (A+1), isso até que o A seja igual a B, ai a função vai retornar recursivamente
;os valores divisiveis por C, que serão somados.

(define (soma-intervalo a b c)
    (cond
      [(> a b) 0]
      [(equal? (remainder a c) 0) (+ a (soma-intervalo (+ a 1) b c))]
      [else (+ (soma-intervalo (+ a 1) b c) 0)]
     ))
    
(examples
  (check-equal? (soma-intervalo 2 10 2) 30) 
  (check-equal? (soma-intervalo 5 2 5) 0) ;
  (check-equal? (soma-intervalo 1 10 11) 0)
  (check-equal? (soma-intervalo 5 7 5) 5)
)