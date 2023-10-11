#lang racket
(require examples)
;PROBLEMA:
;Em algumas situações, é necessário que os digitos de um número sejam escritos
;de forma extensa, ou seja, o númer 174 deve ser escrito como “um-sete-quatro”.
;Faça uma função que receba um valor inteiro positivo e retorne sua escrita extensa.


;Criado uma struct que contém o número e sua forma escrita, criei uma lista com todos os numeros de 0 a 9 e suas formas extensas
;quandor for chamado a função escreve e passado um numero, primeiro é feito a divisão (separação dos numeros) pela separa-digitos, que retorna uma lista,
;essa lista é invertida pois a separa-digitos retorna o inverso dos numeros (separa-digitos 123) -- > '(3 2 1), é invertida em '(1 2 3).
;depois a função nome-numeros, vai chamar a função encontra-nome, que retorna o nome do número recebido, para todos os elementos da lista, e serão todos os
;nomes concatenados, retornando por fim, um string com o nome de cada digito de n.

(struct nome-numero (n nomeN))
(define numeros (list (nome-numero 0 "zero") (nome-numero 1 "um") (nome-numero 2 "dois")
                      (nome-numero 3 "tres") (nome-numero 4 "quatro") (nome-numero 5 "cinco")
                      (nome-numero 6 "seis") (nome-numero 7 "sete") (nome-numero 8 "oito") (nome-numero 9 "nove")))

(define (escreve n)
  ;numero -> lista
  (define (separa-digitos n)
    (cond
      [(= (remainder n 10) 0) empty]
      [else (cons (remainder n 10) (separa-digitos (quotient n 10)))]))

  ;numero -> string
  (define (encontra-nome n numeros)
    (cond
      [(equal? n (nome-numero-n (first numeros)))
       (nome-numero-nomeN (first numeros))] 
      [else (encontra-nome n (rest numeros))]))
  
  ;lista de numeros -> string 
  (define (nome-numeros lista-numeros)
    (cond
      [(empty? lista-numeros) ""]
      [(empty? (rest lista-numeros)) (encontra-nome (first lista-numeros) numeros)]
      [else (string-append (string-append (encontra-nome (first lista-numeros) numeros) "-")
                           (nome-numeros (rest lista-numeros)))]))
  
  (nome-numeros (reverse (separa-digitos n))))

(examples
   (check-equal? (escreve 444) "quatro-quatro-quatro")
   (check-equal? (escreve 8) "oito")
   (check-equal? (escreve 199) "um-nove-nove")
   (check-equal? (escreve 1) "um")
   (check-equal? (escreve 31) "tres-um")
   (check-equal? (escreve 19982) "um-nove-nove-oito-dois")
)