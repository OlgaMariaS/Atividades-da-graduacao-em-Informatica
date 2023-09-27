#lang racket
(require examples)
;Trabalho consiste em:
;receber uma string de palavras, separadas por por " " (espaço),deverá ser convertida em lista
;verificar quantas vezes a palavra se repete na lista, pra isso será verifica o first da lista com o resto e será incrementado em um acumulador
;se chegar ao fim da lista, deverá ir pra proxima palavra
;a palavra com a sua quantidade de repetições, será armazenada em uma nova lista, e esta recebe todas as outras palavras
;quando acabar a contagem de palavras, deverá ser ordenado a nova lista (ordem será pelo numeros de repetições, e caso o n° seja igual, vai pela letra alfabetica
;a lista ordenada que será o retorno final.
;---------------------------------------------------------------------------------------------
(struct qtde_palavra (qtde pal)#:transparent)
(define lista '("a" "b" "b" "c" "d" "a" "e" "b" "d" "a" "e" "c"))
(define text  "a b b c d a e b d a e c")
(define lista1 (list (qtde_palavra 3 "a") (qtde_palavra 3 "b") (qtde_palavra 2 "b") (qtde_palavra 2 "c") (qtde_palavra 2 "d") (qtde_palavra 2 "a") (qtde_palavra 2 "e") (qtde_palavra 1 "b") (qtde_palavra 1 "d") (qtde_palavra 1 "a")(qtde_palavra 1 "e") (qtde_palavra 1 "c")))
(define lista1-sem-a (list (qtde_palavra 3 "b") (qtde_palavra 2 "b") (qtde_palavra 2 "c") (qtde_palavra 2 "d") (qtde_palavra 2 "e") (qtde_palavra 1 "b") (qtde_palavra 1 "d") (qtde_palavra 1 "e") (qtde_palavra 1 "c")))
(define lista2 (list (qtde_palavra 3 "a") (qtde_palavra 3 "b") (qtde_palavra 2 "c") (qtde_palavra 2 "d") (qtde_palavra 2 "e")))

;Converter string em lista
(define (string->lista text)
  (string-split text " "))

;Conta quantidade que x elemento se repete dentro de uma lista
(define (contar lista elemento)
  (cond
    [(empty? lista) 0]
    [(equal? elemento (first lista)) (add1 (contar (rest lista) elemento))]
    [else (contar (rest lista) elemento)]))

;Faz a concatenação entre a palavra e a quantidade de vezes que ela se repete na lista, usando a struct qtde_palavra
(define (concatena lista)
    (qtde_palavra (contar lista (first lista))
                  (first lista)))

;Deve percorrer a lista e criar uma nova, com as palavras e suas quantidades
(define (lista-qtde-pal lista)
  (cond
    [(empty? lista) empty]
    [else (cons (concatena lista) (lista-qtde-pal (rest lista)))]))

;Função que deve remover os elementos repetidos da lista
(define (remove_repetidos lista elemento)
  (cond
    [(empty? lista) empty]
    [(equal? elemento (qtde_palavra-pal (first lista))) (remove_repetidos (rest lista) elemento)]
    [else (cons (first lista) (remove_repetidos (rest lista) elemento))]))

(define (lista-final lista)
  (cond
    [(empty? lista) empty]
    [else (cons (first lista) (lista-final (remove_repetidos lista (qtde_palavra-pal (first lista)))))]))

;Recebe uma lista e retorna ela ordenada usando metodo de ordenação buble sort 
(define (ordena lista)
  (cond
    [(empty? (rest lista)) lista]
    [(> (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
         (cons (first lista)
               (ordena (rest lista)))]
    [(= (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
         (cond
             [(string<? (qtde_palavra-pal (first lista)) (qtde_palavra-pal (first (rest lista))))
              (cons (first lista)
                    (ordena (rest lista)))]
             [else (cons (first (rest lista))
                         (ordena (cons (first lista)
                                       (cdr (rest lista))))) ])]                
    [else (cons (first (rest lista))
                (ordena (cons (first lista)
                              (cdr (rest lista)))))]))

(define (buble lista passadas)
  (cond
    [(equal? (length lista) passadas) lista]
    [else (buble (ordena lista) (add1 passadas))]))
;----------------------------------------------------------------------------------------------
(examples
 (check-equal? (string->lista "a b b c d a e b d a e c") lista)
 (check-equal? (contar lista "a") 3)
 (check-equal? (concatena lista) (qtde_palavra 3 "a"))
 (check-equal? (lista-qtde-pal (string->lista text)) lista1)
 (check-equal? (remove_repetidos lista1 "a") lista1-sem-a)
 (check-equal? (lista-final lista1) lista2)
 (check-equal? (buble lista2 0) lista-ordenada)
)