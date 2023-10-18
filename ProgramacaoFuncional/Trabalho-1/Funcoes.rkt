#lang racket

;; string inteiro -> string
(define (conta-palavras text n)
(struct qtde_palavra (qtde pal)#:transparent)
  
;---------------------------------FUNÇÕES AUXILIARES------------------------------
;Conta quantidade que N elemento se repete dentro de uma lista
(define (contar lista elemento)
  (cond
    [(empty? lista) 0]
    [(equal? elemento (first lista)) (add1 (contar (rest lista) elemento))]
    [else (contar (rest lista) elemento)]))

;Faz a concatenação entre a palavra e a quantidade de vezes que ela se repete na lista, usando a struct qtde_palavra
(define (concatena lista)
    (qtde_palavra (contar lista (first lista))
                  (first lista))) 

;Função que deve remover os elementos repetidos da lista
(define (remove_repetidos lista elemento)
  (cond
    [(empty? lista) empty]
    [(equal? elemento (qtde_palavra-pal (first lista))) (remove_repetidos (rest lista) elemento)]
    [else (cons (first lista) (remove_repetidos (rest lista) elemento))]))

;Recebe uma lista e retorna ela ordenada usando metodo de ordenação bubble sort 
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

;--------------------------------------FUNÇÕES PRINCIPAIS----------------------------------------
;Converter string em lista
(define (string->lista text)
  (string-split text " "))

;Deve percorrer a lista e criar uma nova, com as palavras e suas quantidades
(define (lista-qtde-pal lista)
  (cond
    [(empty? lista) empty]
    [else (cons (concatena lista) (lista-qtde-pal (rest lista)))]))

;Percorre a lista de palavras e suas quantidades e remove palavras repetidas
(define (lista-apos-remocao-repetidos lista)
  (cond
    [(empty? lista) empty]
    [else (cons (first lista) (lista-apos-remocao-repetidos (remove_repetidos lista (qtde_palavra-pal (first lista)))))]))

;Chama a função X vezes que ordena a lista ( X sendo o tamanho da lista ordenada)
(define (bubble-sort lista passadas)
  (cond
    [(equal? (length lista) passadas) lista]
    [else (bubble-sort (ordena lista) (add1 passadas))]))

;---------------------------FUNÇÕES MAIS QUE PRINCIPAIS-------------------------
;Função que converte o texto em lista, conta a quantidade de repetições e cria uma nova lista com as palavras e suas quantidades de forma ordenada pela quantidade
(define (lista-final text)
   (bubble-sort (lista-apos-remocao-repetidos (lista-qtde-pal (string->lista text))) 0))

;Percorre a lista de palavras, retornada por "lista-final", mostrando somente as N primeiras, e adicionando quebra de linha apos cada elemento
(define (mostra-N-da-lista-final lista passadas)                            
  (cond
    [(empty? lista) (display "")]
    [(= n passadas) (display "")]
    [else (display (format "~a ~a ~n" (qtde_palavra-pal (first lista))
                             (number->string (qtde_palavra-qtde (first lista)))))
          (mostra-N-da-lista-final (rest lista) (add1 passadas))]))

(mostra-N-da-lista-final (lista-final text) 0)
)
;---------------------------------------------------------------------------------------------
(define text  "b b c d a e b d a e c e t a e a f b w e a f e a g e a c b b b q c g k l o n h g t teste j j j l c v o o o k")

(conta-palavras text 18)