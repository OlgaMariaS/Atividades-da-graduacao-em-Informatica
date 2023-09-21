#lang racket
(require examples)
;Trabalho consiste em:
;receber uma string de palavras, separadas por por " " (espaço),deverá ser convertida em lista
;verificar quantas vezes a palavra se repete na lista, pra isso será verifica o first da lista com o resto e será incrementado em um acumulador
;se chegar ao fim da lista, deverá ir pra proxima palavra
;a palavra com a sua quantidade de repetições, será armazenada em uma nova lista, e esta recebe todas as outras palavras
;quando acabar a contagem de palavras, deverá ser ordenado a nova lista (ordem será pelo numeros de repetições, e caso o n° seja igual, vai pela letra alfabetica
;a lista ordenada que será o retorno final da conta-palavras

;;funcao que recebe a string contendo as palavras a serem contados e retorna
;;a string a ser escrita no arquivo de saida, onde essa string eh formada
;;por n linhas, onde cada linha contem uma palavra e sua contagem de aparicao na
;;string de entrada.
;; string inteiro -> string
(define (conta-palavras text n)
  text)
;---------------------------------------------------------------------------------------------
(define lista '("a" "b" "b" "c" "d" "a" "e" "b" "d" "a" "e" "c"))
(define text  "a b b c d a e b d a e c")
(define lista1 '("3a" "3b" "2b" "2c" "2d" "2a" "2e" "1b" "1d" "1a" "1e" "1c"))

;Converter string em lista
(define (string->lista text)
  (string-split text " "))

;Conta quantidade que x elemento se repete dentro de uma lista
(define (contar lista elemento)
  (cond
    [(empty? lista) 0]
    [(equal? elemento (first lista)) (add1 (contar (rest lista) elemento))]
    [else (contar (rest lista) elemento)]))

;Faz a concatenação entre a palavra e a quantidade de vezes que ela se repete na lista
(define (concatena lista)
  (string-append (number->string (contar lista (first lista)))
                 (first lista)))

;Deve percorrer a lista e criar uma nova, com os elementos e suas quantidades
;preciso percorrer a lista e remover os elementos que são iguais 
(define (qtde_pal lista)
  (cond
    [(empty? lista) empty]
    [else (cons (concatena lista) (qtde_pal (rest lista)))]))

;Função que deve remover os elementos repetidos da lista
(define (remove_repetidos lista elemento)
  (cond
    [(empty? lista) empty]
    [(equal? elemento (substring(first lista) 1)) (remove_repetidos (rest lista) elemento)]
    [else (cons (first lista) (remove_repetidos (rest lista) elemento))]))

(define (lista-final lista)
  (cond
    [(empty? lista) empty]
    [else (cons (first lista) (lista-final (remove_repetidos lista (substring(first lista) 1))))]))

;----------------------------------------------------------------------------------------------
(examples
 (check-equal? (string->lista "a b b c d a e b d a e c") lista)
 (check-equal? (contar lista "a") 3)
 (check-equal? (concatena lista) "3a")
 (check-equal? (qtde_pal (string->lista text)) '("3a" "3b" "2b" "2c" "2d" "2a" "2e" "1b" "1d" "1a" "1e" "1c"))
 (check-equal? (remove_repetidos lista1 "a") '("3b" "2b" "2c" "2d" "2e" "1b" "1d" "1e" "1c"))
 (check-equal? (lista-final lista1) '("3a" "3b" "2c" "2d" "2e"))
)