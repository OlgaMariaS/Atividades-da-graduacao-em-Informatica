#lang racket
(require examples)
;A conjectura de Goldbach diz que todo número par maior que 4 pode ser escrito pela
;soma de dois números primos. Faça uma função que receba um número par maior que 4
;e retorne uma lista composta por listas de dois números primos compõem a soma
;(quando existirem diversas combinações, deve-se retornar todas). Caso o número não
;seja par ou não seja maior que 4, deverá ser retornada uma lista vazia.
;----------------------------------------------------------------------------------

;Primeiro é criado uma lista dos primos de 2 a N, esse lista vai ser percorrida,
;somando os primos e verificando se são iguais a N, se forem, os elementos da soma, são enviados
;a uma lista de retorno de goldbach, caso não sejam, passa pro proximo primo.


;Função que faz a lista de primos até o numero n
(define (lista-primos n)
  (define (primo? n)
    (cond
      [(= n 2) #t]              ; 2 é primo
      [(= (remainder n 2) 0) #f]; números pares acima de 2 não são primos
      [else
       (let for ([i 3])
         (cond
           [(> i (sqrt n)) #t]        ; nenhum divisor encontrado até a raiz quadrada de n
           [(= (remainder n i) 0) #f] ; n é divisível por i, não é primo
           [else (for (+ i 2))]))]))  ; Verificar o próximo ímpar

    ;Filtra os numeros naturais de 2 a n, pegando somente os primos 
    (filter primo? (stream->list (in-range 2 n))))

;Recebe numero -> retorna lista aninhada
(define (goldbach n)
  (cond
    [(or (< n 4) (> (remainder n 2) 0)) '()]
    [else 
     (let ([lista-primos (lista-primos n)])
       (define (encontra-soma list1 list2)
         (cond
           [(empty? list1) empty]
           [(empty? list2) (encontra-soma (rest list1) lista-primos)]
           [(equal? (+ (first list1) (first list2)) n)
                    (cons (list (first list1) (first list2))
                          (encontra-soma (rest list1) lista-primos))]
           [else (encontra-soma list1 (rest list2))] ))
    
       (encontra-soma lista-primos lista-primos))]))
    
(examples
 (check-equal? (goldbach 16) '((3 13) (5 11) (11 5) (13 3)))
 (check-equal? (goldbach 20) '((3 17) (7 13) (13 7) (17 3)))
 (check-equal? (goldbach 4) '((2 2)))
 (check-equal? (goldbach 2) '())
 (check-equal? (goldbach 15) '())
 (check-equal? (goldbach 22) '((3 19) (5 17) (11 11) (17 5) (19 3)))
)

 
 


